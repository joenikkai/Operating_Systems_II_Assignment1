#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <regex.h>

#include "input.h"
#include "OSIIA1_pattern.h"
#include "OSIIA1_terminal.h"
#include "OSIIA1_threads.h"

#undef DEBUG

volatile int PROGRAM_IS_RUNNING = 1;

volatile uint16_t CPU_IS_EXECUTING = 0;

struct job_instance *CURRENT_JOB = NULL;

volatile int WINDOW_WIDTH = 0;
volatile int WINDOW_HEIGHT = 0;

int RET;
regex_t REGEX;


time_t TIME_QUANTA = 1;
time_t STARTING_TIME = 0;
time_t END_TIME_FOR_PREVIOUS_JOB = 0;

struct Bucket *IN_BUCKET = NULL;
struct Bucket *SUS_BUCKET = NULL;

volatile uint16_t NUMBER_OF_JOBS = 1;

WINDOW *CPU_EXEC_LOG_WIN = NULL;
WINDOW *HANDLE_USER_INPUT_WIN = NULL;
WINDOW *GRANTT_CHART_DISPLAY_WIN = NULL;

int main(int argc, char **argv)
{
    /* initialize ncurses */
    if (!initscr())
    {
        perror("initscr");
        return 1;
    }
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

    int grant_chart_height = 7;
    HANDLE_USER_INPUT_WIN = newwin(1, 0, WINDOW_HEIGHT - grant_chart_height, (int )(WINDOW_WIDTH/2));
    if (!HANDLE_USER_INPUT_WIN)
    {
        perror("newwin");
        return 1;
    }
    CPU_EXEC_LOG_WIN = newwin(1, WINDOW_WIDTH - (int)(WINDOW_WIDTH / 2), WINDOW_HEIGHT - grant_chart_height, (int)(WINDOW_WIDTH / 2));
    if (!CPU_EXEC_LOG_WIN)
    {
        perror("newwin");
        return 1;
    }
    GRANTT_CHART_DISPLAY_WIN = newwin(WINDOW_HEIGHT - grant_chart_height, 0, grant_chart_height, WINDOW_WIDTH);
    if (!CPU_EXEC_LOG_WIN)
    {
        perror("newwin");
        return 1;
    }

    /* border */
    box(HANDLE_USER_INPUT_WIN, 0, 0);
    box(CPU_EXEC_LOG_WIN, 0, 0);
    box(GRANTT_CHART_DISPLAY_WIN, 0, 0);
    return 0;
    /* --- functionality --- */
    STARTING_TIME = time(NULL);
    /* allocate buckets */
    /* incomming buckets */
    IN_BUCKET = calloc(1, sizeof(struct Bucket));

    /* initalize bucket values */
    IN_BUCKET->maximum_ji_accummulation = MAXIMUM_IN_JI_ACCUMULATION;
    IN_BUCKET->ji_accummulation = 0;
    IN_BUCKET->ji = calloc(MAXIMUM_IN_JI_ACCUMULATION + 1, sizeof(struct job_instance*));

    /* suspended bucket */
    SUS_BUCKET = calloc(1, sizeof(struct Bucket));

    /* initalize bucket values */
    SUS_BUCKET->maximum_ji_accummulation = MAXIMUM_SUS_JI_ACCUMULATION;
    SUS_BUCKET->ji_accummulation = 0;
    SUS_BUCKET->ji = calloc(MAXIMUM_SUS_JI_ACCUMULATION + 1, sizeof(struct job_instance*));

#if defined(DEBUG)
    printf("We are here\n");
#endif // DEBUG
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
    RET = regcomp(&REGEX,_OSIIA1_PATTERN,REG_EXTENDED | REG_ICASE);
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
    printf("This program ran for %zu seconds.\n", time(NULL) - STARTING_TIME);
    OSIIA1_print_horirontal_line(NULL, "~", 1);
    OSIIA1_print_horirontal_line(NULL, " ", 1);
    printf("Goodbye. Hope well see you next time.\n");
    OSIIA1_print_horirontal_line(NULL, " ", 2);
    if (IN_BUCKET)
        free_bucket(IN_BUCKET);
    if (SUS_BUCKET)
        free_bucket(SUS_BUCKET);
    return retval;
}
