#include "OSIIA1_threads.h"
#include "timer.h"
#include "OSIIA1_terminal.h"
#include "jobs.h"
#include <string.h>

static void record_execution(struct job_instance *ji)
{
    if (!ji || RECORDS_COUNT >= MAXIMUM_RECORDS)
        return;

    struct job_instance_record *rec = calloc(1, sizeof(struct job_instance_record));
    rec->job_id = ji->job_id;
    rec->burst_time = ji->j->burst;

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
    for (int i = 0; i < RECORDS_COUNT; i++)
    {
        if (RECORDS[i] && RECORDS[i]->job_id == id)
            count++;
    }

    if (count == 1) // Unique/Last one
    {
        free(RECORDS[index]->message);
    }

    free(RECORDS[index]);
    RECORDS[index] = NULL;
}

void *execute_job_instance(void *arg)
{
    int line = 0;
    int inner_height = (getmaxy(CPU_EXEC_LOG_WIN) - 2);

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
            // Record execution slice
            record_execution(CURRENT_JOB);

            // Execute for 1 cycle
            pthread_mutex_unlock(&BUCKET_MUTEX);
            OSIIA1_sleep(TIME_QUANTA);
            pthread_mutex_lock(&BUCKET_MUTEX);

            CURRENT_JOB->j->burst--;

            if (line >= inner_height - 1)
            {
                werase(CPU_EXEC_LOG_WIN);
                box(CPU_EXEC_LOG_WIN, 0, 0);
                line = 0;
            }
            mvwprintw(CPU_EXEC_LOG_WIN, ++line, 1, "executing job [ id: %hx ] | remaining: %hhu", CURRENT_JOB->job_id, CURRENT_JOB->j->burst);
            wrefresh(CPU_EXEC_LOG_WIN);

            if (CURRENT_JOB->j->burst == 0)
            {
                mvwprintw(CPU_EXEC_LOG_WIN, ++line, 1, "executed job [ job id: %hx ]", CURRENT_JOB->job_id);
                mvwprintw(CPU_EXEC_LOG_WIN, ++line, 1, "msg: %s | code: %hhu", CURRENT_JOB->j->e_msg, CURRENT_JOB->j->e_code);
                wrefresh(CPU_EXEC_LOG_WIN);
                
                free_job_instance(CURRENT_JOB);
                CURRENT_JOB = NULL;
            }
        }
        else
        {
            pthread_mutex_unlock(&BUCKET_MUTEX);
            OSIIA1_sleep(TIME_QUANTA); // Idle
            continue;
        }

        pthread_mutex_unlock(&BUCKET_MUTEX);
    }

    return NULL;
}
