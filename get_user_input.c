#include "input.h"
#include "OSIIA1_threads.h"
#define SIGNATURE "vm0001@mmu.ac.ke" /* This is basically meaningless but looks cool */
#include <string.h>

char *get_user_input()
{
    char *input_buffer = OSIIA1_readline(&HANDLE_USER_INPUT_INNER_WIN,SIGNATURE "$ >  "); /* implement your own readline */
    if (strlen(input_buffer) > 0) OSIIA1_add_history(&HANDLE_USER_INPUT_INNER_WIN,input_buffer);
    return input_buffer;
}
