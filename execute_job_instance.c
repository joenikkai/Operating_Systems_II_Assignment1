#include "OSIIA1_threads.h"
#include "timer.h"

void *execute_job_instance(void *arg)
{
    while (PROGRAM_IS_RUNNING)
    {
        OSIIA1_sleep(TIME_QUANTA);
        printf("\nexecution cycle");
    }

    return NULL;
}