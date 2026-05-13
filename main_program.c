#include "input.h"
#include "pattern.h"

int main_program(int argc, char **argv)
{
    char *input;
    while ((input = get_user_input()) && tolower(input[0]) != 'q')
    {
        if (strlen(input) > 0)
            printf("%s\n", input);
        free(input);
    }
    if (input)
        free(input);
    return 0;
}
