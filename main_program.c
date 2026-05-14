#include "input.h"
#include "pattern.h"
#include "jobs.h"
#include "timer.h"

int main_program(int argc, char **argv)
{
    char *input;
    while ((input = get_user_input()) && strcmp(OSIIA1_strn_to_lower(input, (size_t)strlen(input)), "quit") != 0)
    {
        if (strlen(input) <= 0)
        {
            continue;
        }
            struct extracted_strings *es = extract_data_from_string(input);
        if (!es) {
            printf("command not found: %s\n", input);
            continue;
        }

        /* make a new job */
        struct Job *new_job = get_new_job(es);
        if (!new_job) {
            printf("could not make a new job\n");
            continue;
        }
        printf("arrival time: %zu | burst time: %hhu | exit message: %s | exit code: %hhu\n",new_job->arrival_time,new_job->burst,new_job->e_msg,new_job->e_code);
        free_extracted_strings(es);
        free(input);
    }
    if (input)
        free(input);
    return 0;
}
