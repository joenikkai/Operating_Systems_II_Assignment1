#include "input.h"
// #include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"
#include "OSIIA1_terminal.h"

#undef DEBUG

void *handle_user_input(void* args)
{
    while (PROGRAM_IS_RUNNING)
    {
        
        char *input = get_user_input();
        
        if (strcmp(OSIIA1_strn_to_lower(OSIIA1_trim_leading_and_trailing_whitespace(input), (size_t)strlen(input)), "exit") == 0)
        {
            PROGRAM_IS_RUNNING = 0;
            return NULL;
        }

        if (strlen(input) <= 0)
            return NULL;
        /* --- */
        
        struct extracted_strings *es = extract_data_from_string(input);
        if (!es)
        {
            wprintw(HANDLE_USER_INPUT_WIN,"command `%s' not found.\n", input);
            return NULL;
        }

        /* make a new job */
        struct Job *new_job = get_new_job(es);
        if (!new_job)
        {
            wprintw(HANDLE_USER_INPUT_WIN,"could not make a new job\n");
            return NULL;
        }
    #if defined(DEBUG)
        wprintw(HANDLE_USER_INPUT_WIN,"arrival time: %zu | burst time: %hhu | exit message: %s | exit code: %hhu\n", new_job->arrival_time, new_job->burst, new_job->e_msg, new_job->e_code);
    #endif // DEBUG

        if (IN_BUCKET->ji_accummulation <= MAXIMUM_IN_JI_ACCUMULATION)
        {
            push_new_job_instance(new_job);
    #if defined(DEBUG)
            wprintw(HANDLE_USER_INPUT_WIN,"After pushing the new instance\n");
    #endif // DEBUG
            wprintw(HANDLE_USER_INPUT_WIN,"appended job  [ job id: %hx ]\n",IN_BUCKET->ji[IN_BUCKET->ji_accummulation-1]->job_id);
        }
        else
        {
            wprintw(HANDLE_USER_INPUT_WIN,"maximum number of jobs at a time is reached wait for the program to complete execution\n");
        }

        free_job(new_job);
        free_extracted_strings(es);
        
        if (input)
            free(input);
        /* --- */
    }
    return NULL;
}