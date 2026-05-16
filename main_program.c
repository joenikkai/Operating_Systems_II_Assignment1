#include "input.h"
#include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"

int main_program(int argc, char **argv)
{
    OSIIA1_thread_t cpu_thread;

    int retval = 0;
    while (PROGRAM_IS_RUNNING)
    {
        handle_user_input();

    }

    return retval;
}
