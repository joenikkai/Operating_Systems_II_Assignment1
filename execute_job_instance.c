#include "OSIIA1_threads.h"
#include "timer.h"
#include "OSIIA1_terminal.h"

void *execute_job_instance(void *arg)
{
    while (PROGRAM_IS_RUNNING)
    {
        OSIIA1_sleep(TIME_QUANTA);
        wprintw(CPU_EXEC_LOG_WIN, "\nexecution cycle");
    }

    return NULL;
}