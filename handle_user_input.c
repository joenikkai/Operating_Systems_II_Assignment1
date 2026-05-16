#include "input.h"
// #include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"

void handle_user_input()
{
    char *input = get_user_input();
    
    if (strcmp(OSIIA1_strn_to_lower(input, (size_t)strlen(input)), "exit") == 0)
    {
        PROGRAM_IS_RUNNING = 0;
        return;
    }

    if (strlen(input) <= 0)
        return;
    /* --- */
    
    struct extracted_strings *es = extract_data_from_string(input);
    if (!es)
    {
        printf("command `%s' not found.\n", input);
        return;
    }

    if (in_bucket->ji_accummulation < MAXIMUM_IN_JI_ACCUMULATION)
    {
        printf("maximum number of jobs at a time is reached wait for the program to complete execution");

        free_extracted_strings(es);
        free(input);

        if (input)
            free(input);
        /* --- */
    }

    /* make a new job */
    struct Job *new_job = get_new_job(es);
    if (!new_job)
    {
        printf("could not make a new job\n");
        return;
    }
#if defined(DEBUG)
    printf("arrival time: %zu | burst time: %hhu | exit message: %s | exit code: %hhu\n", new_job->arrival_time, new_job->burst, new_job->e_msg, new_job->e_code);
#endif // DEBUG

    if (in_bucket->ji_accummulation <= MAXIMUM_IN_JI_ACCUMULATION)
    {
        push_new_job_instance(new_job);
    }
    printf("maximum number of jobs at a time is reached wait for the program to complete execution");

    free_extracted_strings(es);
    free(input);
    
    if (input)
        free(input);
    /* --- */
    return;
}