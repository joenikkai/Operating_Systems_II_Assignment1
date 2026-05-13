#include "input.h"
#include "pattern.h"
#include "jobs.h"

int main_program(int argc, char **argv)
{
    char *input;
    while ((input = get_user_input()) && tolower(input[0]) != 'q')
    {
        struct extracted_strings *es = extract_data_from_string(input);
        if (!es && strlen(input) > 0) {
            printf("NO MATCH: %s\n", input);
            continue;
        }

        /* make a new job */
        struct Job *new_job = get_new_job(es);
        if (!new_job) {
            printf("could not make a new job\n");
            continue;
        }

        free_extracted_strings(es);
        free(input);
    }
    if (input)
        free(input);
    return 0;
}
