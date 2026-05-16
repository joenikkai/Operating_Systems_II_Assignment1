#include "input.h"
#include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"

int main_program(int argc, char **argv)
{
    OSIIA1_thread_t cpu_thread;
#if defined(__WIN32)
#elif defined(__unix__)
#else
#error PLATFORM_COMPATIBILITY_ERROR
#endif
    int retval = 0;
    while (PROGRAM_IS_RUNNING)
    {
        handle_user_input();

    }

    return retval;
}
