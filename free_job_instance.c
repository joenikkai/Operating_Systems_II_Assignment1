#include "OSIIA1_threads.h"

void free_job_instance(struct job_instance *ji)
{
    if (!ji)
        return;
    /* --- */
    
    free_job(ji->j);
    free(ji);
}
