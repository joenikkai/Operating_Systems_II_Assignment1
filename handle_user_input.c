#include "input.h"
// #include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"
#include "OSIIA1_terminal.h"
#include <string.h>
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
