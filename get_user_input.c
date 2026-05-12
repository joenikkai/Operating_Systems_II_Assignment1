#include "input.h"
#define SIGNATURE "vm0001@mmu.ac.ke" /* This is basically meaningless but looks cool */

char *get_user_input()
{
    return readline(SIGNATURE "$ >");
}
