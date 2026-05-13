#include "input.h"
#define SIGNATURE "vm0001@mmu.ac.ke" /* This is basically meaningless but looks cool */

char *get_user_input()
{
    char *input_buffer = readline(SIGNATURE "$ >");
    if (strlen(input_buffer) > 0) add_history(input_buffer);
    return input_buffer;
}
