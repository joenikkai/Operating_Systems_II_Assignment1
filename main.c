#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <regex.h>

#include "input.h"
#include "pattern.h"
#include "OSIIA1_terminal.h"

int *WINDOW_WIDTH;
int *WINDOW_HEIGHT;

int RET;
regex_t REGEX;


int main(int argc,char **argv)
{
    get_current_terminal_width(WINDOW_HEIGHT, WINDOW_WIDTH);
    printf(BOOTING_SEQUENCE);
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
    return retval;
}
