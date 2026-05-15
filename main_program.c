#include "input.h"
#include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"

int main_program(int argc, char **argv)
{
    int retval = 0;
    while (program_is_running)
    {
        retval = handle_user_input(argc, argv);
    }

    return retval;
}
