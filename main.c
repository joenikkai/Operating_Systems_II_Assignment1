#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <regex.h>

#include "input.h"

#define BOOTING_SEQUENCE "$ > 9  \"Execution of write file syscall\" 0\n" \
    "    ^          ^                           ^\n" \
    "    |          |                           |\n" \
    "    |          |                          This is the exitcode of the thread\n" \
    "    |          This is what to print after a job has been executed\n" \
    "    This is the burst time if the job in seconds\n" \
    "qQ to quit\n"

int main()
{
    printf( BOOTING_SEQUENCE);
    read_history(HISTORY_FILE);
    stifle_history(HISTORY_MAX);

    /* initialize regex */
    RET = regcomp(&REGEX,PATTERN,REG_EXTENDED | REG_ICASE);
    if (RET) {
        char errbuff[1024];
        regerror(RET,&REGEX,errbuff,sizeof(errbuff));
        fprintf(stderr,"regcomp failed: %s\n",errbuff);
    }

    char *input;
    while ((input = get_user_input()) && tolower(input[0]) != 'q')
    {
        if (strlen(input)> 0) 
            printf("%s\n", input);
        free(input);
    }
    if (input)
        free(input);
    /* the write history must exists */
    write_history(HISTORY_FILE);
    return 0;
}
