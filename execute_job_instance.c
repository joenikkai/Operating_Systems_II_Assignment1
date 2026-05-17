#include "OSIIA1_threads.h"
#include "timer.h"
#include "OSIIA1_terminal.h"
#include "jobs.h"
#include <string.h>

static void record_execution(struct job_instance *ji)
{
    if (!ji || RECORDS_COUNT >= MAXIMUM_RECORDS)
        return;

    // Check if we can consolidate with the last record
    if (RECORDS_COUNT > 0)
    {
        struct job_instance_record *last = RECORDS[RECORDS_COUNT - 1];
        if (last->job_id == ji->job_id)
        {
            last->duration++;
            last->burst_time = ji->j->burst;
            if (ji->j->burst == 0)
            {
                long sim_time = 0;
                for(int i=0; i<RECORDS_COUNT-1; i++) sim_time += RECORDS[i]->duration;
                last->finish_time = sim_time + last->duration;
            }
            return;
        }
    }

    struct job_instance_record *rec = calloc(1, sizeof(struct job_instance_record));
    rec->job_id = ji->job_id;
    rec->burst_time = ji->j->burst;
    rec->arrival_time = ji->j->arrival_time - STARTING_TIME;
    rec->original_burst = ji->j->original_burst;
    rec->exit_code = ji->j->e_code;
    rec->duration = 1;
    
    // We'll calculate finish time in the query command by summing durations
    // or we can store the current simulation time here.
    // Let's use the current RECORDS sum as a proxy for simulation time.
    long sim_time = 0;
    for(int i=0; i<RECORDS_COUNT; i++) sim_time += RECORDS[i]->duration;
    
    if (ji->j->burst == 0)
        rec->finish_time = sim_time + 1;

    // String sharing logic
    rec->message = NULL;
    for (int i = 0; i < RECORDS_COUNT; i++)
    {
        if (RECORDS[i] && RECORDS[i]->job_id == ji->job_id)
        {
            rec->message = RECORDS[i]->message;
            break;
        }
    }

    if (!rec->message)
    {
        rec->message = strdup(ji->j->e_msg);
    }

    RECORDS[RECORDS_COUNT++] = rec;
}

static void free_record(int index)
{
    if (index < 0 || index >= RECORDS_COUNT || !RECORDS[index])
        return;

    uint16_t id = RECORDS[index]->job_id;
    int count = 0;
    // We only free the message if this is the LAST record with this job_id in the array
    for (int i = index + 1; i < RECORDS_COUNT; i++)
    {
        if (RECORDS[i] && RECORDS[i]->job_id == id)
        {
            count++;
            break;
        }
    }

    if (count == 0) // This is the last one
    {
        free(RECORDS[index]->message);
    }

    free(RECORDS[index]);
    RECORDS[index] = NULL;
}

void free_records()
{
    if (!RECORDS) return;
    pthread_mutex_lock(&BUCKET_MUTEX);
    for (int i = 0; i < RECORDS_COUNT; i++)
    {
        free_record(i);
    }
    free(RECORDS);
    RECORDS = NULL;
    RECORDS_COUNT = 0;
    pthread_mutex_unlock(&BUCKET_MUTEX);
}

void *execute_job_instance(void *arg)
{
    int line = 0;
    int inner_height = getmaxy(CPU_EXEC_LOG_INNER_WIN);

    while (PROGRAM_IS_RUNNING)
    {
        pthread_mutex_lock(&BUCKET_MUTEX);

        struct job_instance *shortest_job = NULL;
        int shortest_bucket = -1; // 0 for IN, 1 for SUS
        int shortest_idx = -1;
        uint8_t min_burst = 255;

        if (CURRENT_JOB)
        {
            min_burst = CURRENT_JOB->j->burst;
        }

        // Check IN_BUCKET
        for (int i = 0; i < IN_BUCKET->ji_accummulation; i++)
        {
            if (IN_BUCKET->ji[i]->j->burst < min_burst)
            {
                min_burst = IN_BUCKET->ji[i]->j->burst;
                shortest_job = IN_BUCKET->ji[i];
                shortest_bucket = 0;
                shortest_idx = i;
            }
        }

        // Check SUS_BUCKET
        for (int i = 0; i < SUS_BUCKET->ji_accummulation; i++)
        {
            if (SUS_BUCKET->ji[i]->j->burst < min_burst)
            {
                min_burst = SUS_BUCKET->ji[i]->j->burst;
                shortest_job = SUS_BUCKET->ji[i];
                shortest_bucket = 1;
                shortest_idx = i;
            }
        }

        // Preemption logic
        if (shortest_job)
        {
            if (CURRENT_JOB)
            {
                // Suspend current job
                SUS_BUCKET->ji[SUS_BUCKET->ji_accummulation++] = CURRENT_JOB;
            }

            // Load new job
            CURRENT_JOB = shortest_job;

            // Remove from its bucket
            struct Bucket *b = (shortest_bucket == 0) ? IN_BUCKET : SUS_BUCKET;
            for (int i = shortest_idx; i < b->ji_accummulation - 1; i++)
            {
                b->ji[i] = b->ji[i + 1];
            }
            b->ji_accummulation--;
        }

        if (CURRENT_JOB)
        {
            // Execute for 1 cycle
            pthread_mutex_unlock(&BUCKET_MUTEX);
            OSIIA1_sleep(TIME_QUANTA);
            pthread_mutex_lock(&BUCKET_MUTEX);

            CURRENT_JOB->j->burst--;
            
            // Record execution slice (after decrement)
            record_execution(CURRENT_JOB);

            if (line >= inner_height - 3)
            {
                pthread_mutex_lock(&TERMINAL_MUTEX);
                werase(CPU_EXEC_LOG_INNER_WIN);
                line = 0;
                pthread_mutex_unlock(&TERMINAL_MUTEX);
            }
            pthread_mutex_lock(&TERMINAL_MUTEX);
            mvwprintw(CPU_EXEC_LOG_INNER_WIN, ++line, 1, "CPU Executing [ ID: %hx ]", CURRENT_JOB->job_id);
            mvwprintw(CPU_EXEC_LOG_INNER_WIN, ++line, 1, "  Message: %s", CURRENT_JOB->j->e_msg);
            mvwprintw(CPU_EXEC_LOG_INNER_WIN, ++line, 1, "  Burst Remaining: %hhu s", CURRENT_JOB->j->burst);
            wrefresh(CPU_EXEC_LOG_INNER_WIN);
            pthread_mutex_unlock(&TERMINAL_MUTEX);

            if (CURRENT_JOB->j->burst == 0)
            {
                pthread_mutex_lock(&TERMINAL_MUTEX);
                mvwprintw(CPU_EXEC_LOG_INNER_WIN, ++line, 1, ">> Job %hx Finished (Code: %hhu)", CURRENT_JOB->job_id, CURRENT_JOB->j->e_code);
                wrefresh(CPU_EXEC_LOG_INNER_WIN);
                pthread_mutex_unlock(&TERMINAL_MUTEX);
                
                free_job_instance(CURRENT_JOB);
                CURRENT_JOB = NULL;
            }
        }
        else
        {
            pthread_mutex_unlock(&BUCKET_MUTEX);
            pthread_mutex_lock(&TERMINAL_MUTEX);
            werase(CPU_EXEC_LOG_INNER_WIN);
            mvwprintw(CPU_EXEC_LOG_INNER_WIN, 1, 1, "CPU STATUS: IDLE");
            wrefresh(CPU_EXEC_LOG_INNER_WIN);
            pthread_mutex_unlock(&TERMINAL_MUTEX);
            line = 1;
            OSIIA1_sleep(TIME_QUANTA); // Idle
            continue;
        }

        pthread_mutex_unlock(&BUCKET_MUTEX);
    }

    return NULL;
}
