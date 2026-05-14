#include "jobs.h"
#include "input.h"

struct Job *get_new_job(struct extracted_strings* es) /* makes a new `struct Job` and assigns the the submatches of extracted strings while ignoring the full match */
{
    struct Job *new_job = calloc(1,sizeof(struct Job));
    if (!new_job)
    {
        perror("calloc");
        return NULL;
    }
    new_job->arrival_time = time(NULL);
    new_job->burst = (uint8_t)atoi(es->strings[1]);
    new_job->e_msg = calloc(es->length_of_strings[2]+1, sizeof(char));
    new_job->e_code = (uint8_t)atoi(es->strings[3]);
    snprintf(new_job->e_msg,es->length_of_strings[2],"%.*s",es->length_of_strings[2],es->strings[2]);
    return new_job;
}