#include "OSIIA1_threads.h"
#include "timer.h"
#include "OSIIA1_terminal.h"

void *execute_job_instance(void *arg)
{
    int line = 0;
    int inner_height = (getmaxy(CPU_EXEC_LOG_WIN) - 2);
    while (PROGRAM_IS_RUNNING)
    {
        if (line >= inner_height - 1)
            line = 0;
        OSIIA1_sleep(TIME_QUANTA);
        mvwprintw(CPU_EXEC_LOG_WIN,line++,1, "execution cycle");
    }

    return NULL;
}