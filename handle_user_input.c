#include "input.h"
// #include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"
#include "OSIIA1_terminal.h"
#include <string.h>
#include <ctype.h>
#undef DEBUG

void *handle_user_input(void* args)
{
    while (PROGRAM_IS_RUNNING)
    {
        char *input = get_user_input();
        if (!input) continue;

        char *trimmed = OSIIA1_trim_leading_and_trailing_whitespace(input);
        char *lower = OSIIA1_strn_to_lower(trimmed, strlen(trimmed));
        
        if (strcmp(lower, "exit") == 0)
        {
            free(lower);
            free(input);
            PROGRAM_IS_RUNNING = 0;
            return NULL;
        }

        if (strcmp(lower, "clear") == 0)
        {
            wclear(HANDLE_USER_INPUT_INNER_WIN);
            wrefresh(HANDLE_USER_INPUT_INNER_WIN);
            free(lower);
            free(input);
            continue;
        }

        if (strncmp(lower, "ls", 2) == 0)
        {
            char *arg = trimmed + 2;
            while (isspace((unsigned char)*arg)) arg++;

            if (strcmp(arg, "in") == 0)
            {
                pthread_mutex_lock(&BUCKET_MUTEX);
                wprintw(HANDLE_USER_INPUT_INNER_WIN, "Incoming Jobs:\n");
                for (int i = 0; i < IN_BUCKET->ji_accummulation; i++)
                {
                    wprintw(HANDLE_USER_INPUT_INNER_WIN, " [ ID: %hx ] Burst: %hhu | Msg: %s\n", 
                            IN_BUCKET->ji[i]->job_id, IN_BUCKET->ji[i]->j->burst, IN_BUCKET->ji[i]->j->e_msg);
                }
                pthread_mutex_unlock(&BUCKET_MUTEX);
            }
            else if (strcmp(arg, "sus") == 0)
            {
                pthread_mutex_lock(&BUCKET_MUTEX);
                wprintw(HANDLE_USER_INPUT_INNER_WIN, "Suspended Jobs:\n");
                for (int i = 0; i < SUS_BUCKET->ji_accummulation; i++)
                {
                    wprintw(HANDLE_USER_INPUT_INNER_WIN, " [ ID: %hx ] Burst: %hhu | Msg: %s\n", 
                            SUS_BUCKET->ji[i]->job_id, SUS_BUCKET->ji[i]->j->burst, SUS_BUCKET->ji[i]->j->e_msg);
                }
                pthread_mutex_unlock(&BUCKET_MUTEX);
            }
            else if (strcmp(arg, "done") == 0)
            {
                pthread_mutex_lock(&BUCKET_MUTEX);
                wprintw(HANDLE_USER_INPUT_INNER_WIN, "Completed Jobs:\n");
                // Find unique job IDs that finished (last record burst was 1)
                for (int i = 0; i < RECORDS_COUNT; i++)
                {
                    if (RECORDS[i] && RECORDS[i]->burst_time == 1)
                    {
                        wprintw(HANDLE_USER_INPUT_INNER_WIN, " [ ID: %hx ] Msg: %s\n", 
                                RECORDS[i]->job_id, RECORDS[i]->message);
                    }
                }
                pthread_mutex_unlock(&BUCKET_MUTEX);
            }
            else
            {
                wprintw(HANDLE_USER_INPUT_INNER_WIN, "Usage: ls [in|sus|done]\n");
            }
            wrefresh(HANDLE_USER_INPUT_INNER_WIN);
            free(lower);
            free(input);
            continue;
        }
        free(lower);

        if (strlen(trimmed) <= 0)
        {
            free(input);
            continue;
        }
        /* --- */
        
        struct extracted_strings *es = extract_data_from_string(trimmed);
        if (!es)
        {
            wprintw(HANDLE_USER_INPUT_INNER_WIN, "command `%s' not found.\n", trimmed);
            wrefresh(HANDLE_USER_INPUT_INNER_WIN);
            free(input);
            continue;
        }

        /* make a new job */
        struct Job *new_job = get_new_job(es);
        if (!new_job)
        {
            wprintw(HANDLE_USER_INPUT_INNER_WIN, "could not make a new job\n");
            wrefresh(HANDLE_USER_INPUT_INNER_WIN);
            free_extracted_strings(es);
            free(input);
            continue;
        }
    #if defined(DEBUG)
        wprintw(HANDLE_USER_INPUT_INNER_WIN,"arrival time: %zu | burst time: %hhu | exit message: %s | exit code: %hhu\n", new_job->arrival_time, new_job->burst, new_job->e_msg, new_job->e_code);
    #endif // DEBUG

        pthread_mutex_lock(&BUCKET_MUTEX);
        if (IN_BUCKET->ji_accummulation <= MAXIMUM_IN_JI_ACCUMULATION)
        {
            push_new_job_instance(new_job);
    #if defined(DEBUG)
            wprintw(HANDLE_USER_INPUT_INNER_WIN,"After pushing the new instance\n");
    #endif // DEBUG
            wprintw(HANDLE_USER_INPUT_INNER_WIN,"appended job  [ job id: %hx ]\n",IN_BUCKET->ji[IN_BUCKET->ji_accummulation-1]->job_id);
            wrefresh(HANDLE_USER_INPUT_INNER_WIN);
        }
        else
        {
            wprintw(HANDLE_USER_INPUT_INNER_WIN,"maximum number of jobs at a time is reached wait for the program to complete execution\n");
            wrefresh(HANDLE_USER_INPUT_INNER_WIN);
        }
        pthread_mutex_unlock(&BUCKET_MUTEX);

        free_job(new_job);
        free_extracted_strings(es);
        
        if (input)
            free(input);
        /* --- */
    }
    return NULL;
}
