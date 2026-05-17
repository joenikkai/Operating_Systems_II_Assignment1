#if !defined(MAIN_H)

#define MAIN_H

#define PROGRAM_NAME "Operating_Systems_II_Assignment1"
#define VERSION "1.0.0"

#define PLATFORM_COMPATIBILITY_ERROR "This code might not work for your platfrom. Make custom code that works for your platform and submit it to us\n"

#include "input.h"
#include "OSIIA1_pattern.h"

#define BOOTING_SEQUENCE { \
        "",\
        "",\
        "<=>", \
        "$ > 9  \"Execution of write file syscall\" 0", \
        "    ^          ^                           ^", \
        "    |          |                           |", \
        "    |          |                           This is the exitcode of the thread", \
        "    |          This is what to print after a job has been executed", \
        "    This is the burst time if the job in seconds", \
        "(exitEXIT) to exit the program", \
        "",\
        "",\
        "<->",\
        "Yay! Welcome, Dear User.", \
        "<->" \
    }
/* end of defines */

#define DEBUG

int main_program(int argc, char **argv);
#if defined(TEST_THIS_CODE)
int testing_program(int argc, char **argv);
#endif // TEST_THIS_CODE

char *OSIIA1_strn_to_lower(char *s, size_t l);
char *OSIIA1_trim_leading_and_trailing_whitespace(char *s);


extern volatile int PROGRAM_IS_RUNNING; /* set to 0 so as to stop the pro */

#endif // MAIN_H