#if !defined(JOBS_H)
#define JOBS_H

#include <stdlib.h>
#include <stdint.h>
#include "pattern.h"
struct Job
{
    time_t arrival_time;
    uint8_t burst;
    uint8_t e_code;
    char *e_msg;
};

struct Job *get_new_job(struct extracted_strings* es);
void free_job();
time_t get_job_burst_time(struct Job *j);
#endif // JOBS_H