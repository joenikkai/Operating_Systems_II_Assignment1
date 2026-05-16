#if !defined(JOBS_H)
#define JOBS_H

#include <stdlib.h>
#include <stdint.h>
#include "OSIIA1_pattern.h"
struct Job
{
    time_t arrival_time;
    uint8_t burst;
    uint8_t e_code;
    char *e_msg;
};

struct Job *get_new_job(struct extracted_strings* es);
void free_job(struct Job *j);

inline time_t get_job_burst_time(struct Job *j)
{
    return j->burst;
}

void push_new_job_instance(struct Job *j);
void pop_instance_to(void *src, void *dest);

#endif // JOBS_H