#include "main.h"
#include "OSIIA1_terminal.h"

void OSIIA1_play_boot_sequence() 
{
    OSIIA1_print_horirontal_line(NULL, " ", 2);
    OSIIA1_print_horirontal_line(NULL, "=", 1);
    printf(BOOTING_SEQUENCE);
    OSIIA1_print_horirontal_line(NULL, NULL, 1);
    printf("Yay! Welcome dear user.\n");
    OSIIA1_print_horirontal_line(NULL, " ", 2);
}