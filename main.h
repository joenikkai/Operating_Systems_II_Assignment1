#if !defined(MAIN_H)

#define MAIN_H

#define PROGRAM_NAME "Operating_Systems_II_Assignment1"

#include "input.h"
#include "pattern.h"

#define BOOTING_SEQUENCE "$ > 9  \"Execution of write file syscall\" 0\n" \
    "    ^          ^                          ^\n" \
    "    |          |                          |\n" \
    "    |          |                          This is the exitcode of the thread\n" \
    "    |          This is what to print after a job has been executed\n" \
    "    This is the burst time if the job in seconds\n" \
    "qQ to quit\n"
/* end of defines */

int main_program(int argc, char **argv);
#if defined(TEST_THIS_CODE)
int testing_program(int argc, char **argv);
#endif // TEST_THIS_CODE

#endif // MAIN_H