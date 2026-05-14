#include "jobs.h"

time_t get_job_burst_time(struct Job* j)
{
    return j->burst;
}