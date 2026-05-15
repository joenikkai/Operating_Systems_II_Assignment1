#if !defined(MAIN_H)

#define MAIN_H

#define PROGRAM_NAME "Operating_Systems_II_Assignment1"

#define PLATFORM_COMPATIBILITY_ERROR "This code might not work for your platfrom. Make custom code that works for your platform and submit it to us\n"

#include "input.h"
#include "pattern.h"

#define BOOTING_SEQUENCE "$ > 9  \"Execution of write file syscall\" 0\n" \
    "    ^          ^                          ^\n" \
    "    |          |                          |\n" \
    "    |          |                          This is the exitcode of the thread\n" \
    "    |          This is what to print after a job has been executed\n" \
    "    This is the burst time if the job in seconds\n" \
    "(exitEXIT) to exit the program\n"
/* end of defines */

#define DEBUG

int main_program(int argc, char **argv);
#if defined(TEST_THIS_CODE)
int testing_program(int argc, char **argv);
#endif // TEST_THIS_CODE
char *OSIIA1_strn_to_lower(char *s, size_t l);

extern int WINDOW_WIDTH; /* \brief The width of the current terminal */
extern int WINDOW_HEIGHT;/* \brief The height of the current terminal */

extern volatile int program_is_running; /* set to 0 so as to stop the pro */

#endif // MAIN_H