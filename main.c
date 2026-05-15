#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <regex.h>

#include "input.h"
#include "pattern.h"
#include "OSIIA1_terminal.h"
#include "OSIIA1_threads.h"

#undef DEBUG

volatile int program_is_running = 1;

int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;

int RET;
regex_t REGEX;


time_t time_quanta = 1;
time_t starting_time = 0;
time_t end_time_for_previous_job = 0;

struct Bucket *in_bucket = NULL;
struct Bucket *sus_bucket = NULL;

uint16_t NUMBER_OF_JOBS = 1;

int main(int argc, char **argv)
{
    starting_time = time(NULL);
    /* allocate buckets */
    /* incomming buckets */
    in_bucket = calloc(1, sizeof(struct Bucket));

    /* initalize bucket values */
    in_bucket->maximum_ji_accummulation = MAXIMUM_IN_JI_ACCUMULATION;
    in_bucket->ji_accummulation = 0;
    in_bucket->ji = calloc(MAXIMUM_IN_JI_ACCUMULATION + 1, sizeof(struct job_instance));

    /* suspended bucket */
    sus_bucket = calloc(1, sizeof(struct Bucket));

    /* initalize bucket values */
    sus_bucket->maximum_ji_accummulation = MAXIMUM_SUS_JI_ACCUMULATION;
    sus_bucket->ji_accummulation = 0;
    sus_bucket->ji = calloc(MAXIMUM_SUS_JI_ACCUMULATION + 1, sizeof(struct job_instance));

#if defined(DEBUG)
    printf("We are here\n");
#endif // DEBUG
    get_current_terminal_width(&WINDOW_HEIGHT, &WINDOW_WIDTH);
    if (!WINDOW_HEIGHT)
    {
        printf("Could not assign window height value.\n");
        return 1;
    }
    if (!WINDOW_WIDTH)
    {
        printf("Could not assign window width value.\n");
        return 1;
    }
    OSIIA1_print_horirontal_line(NULL, " ", 2);
    OSIIA1_print_horirontal_line(NULL, "=", 1);
    printf(BOOTING_SEQUENCE);
    OSIIA1_print_horirontal_line(NULL, NULL, 1);
    printf("Yay! Welcome dear user.\n");
    OSIIA1_print_horirontal_line(NULL, " ", 2);
    read_history(HISTORY_FILE);
    stifle_history(HISTORY_MAX);
    
    /* return value */
    int retval = 0;

    /* initialize regex */
    RET = regcomp(&REGEX,PATTERN,REG_EXTENDED | REG_ICASE);
    if (RET) {
        char errbuff[1024];
        regerror(RET,&REGEX,errbuff,sizeof(errbuff));
        fprintf(stderr,"regcomp failed: %s\n",errbuff);
    }

#if defined(TEST_THIS_CODE)
    retval = testing_program(argc,argv);
#else
    retval = main_program(argc, argv);
#endif // TEST_THIS_CODE

    /* the write history must exists */
    write_history(HISTORY_FILE);
    OSIIA1_print_horirontal_line(NULL, " ", 1);
    OSIIA1_print_horirontal_line(NULL, "-", 1);
    printf("This program ran for %zu seconds.\n", time(NULL) - starting_time);
    OSIIA1_print_horirontal_line(NULL, "~", 1);
    OSIIA1_print_horirontal_line(NULL, " ", 1);
    printf("Goodbye. Hope well see you next time.\n");
    OSIIA1_print_horirontal_line(NULL, " ", 2);
    if (in_bucket)
        free_bucket(in_bucket);
    if (sus_bucket)
        free_bucket(sus_bucket);
    return retval;
}
