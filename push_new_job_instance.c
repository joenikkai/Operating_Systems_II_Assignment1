#include "OSIIA1_threads.h"
#include "jobs.h"

void push_new_job_instance(struct Job* j)
{
    struct job_instance ji = {
        .j = j,
        .job_id = NUMBER_OF_JOBS++
    };
    in_bucket->ji[in_bucket->ji_accummulation++] = ji;
}
