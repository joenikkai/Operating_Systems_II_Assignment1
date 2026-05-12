#if !defined(INPUT_H)
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "main.h"


#define HISTORY_FILE "."PROGRAM_NAME"_history"
#define HISTORY_MAX  100

char *get_user_input();

#endif // INPUT_H