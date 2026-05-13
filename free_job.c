#include "jobs.h"

void free_job(struct Job* j)
{
    if (!j)
        return;
    if(j->e_msg)
        free(j->e_msg);
    free(j);
}