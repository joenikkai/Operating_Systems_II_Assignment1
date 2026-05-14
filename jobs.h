#if !defined(JOBS_H)
#define JOBS_H

#include <stdlib.h>
#include <stdint.h>
#include "pattern.h"
struct Job
{
    time_t arrival_time;
    uint8_t wait;
    uint8_t e_code;
    char *e_msg;
};

struct Job *get_new_job(struct extracted_strings* es);
void free_job();
void exit_job();
#endif // JOBS_H