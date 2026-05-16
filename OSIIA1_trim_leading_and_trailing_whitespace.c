#include "main.h"

char *OSIIA1_trim_leading_and_trailing_whitespace(char *s)
{
    char *str = strdup(s);

    char *start = str;
    char *end = str + strlen(str) - 1;
    while (isspace((unsigned char)*start))
        start++;
    while (end > start && isspace((unsigned char)*end))
        end--;
    size_t len = end - start + 1;
    str[len] = '\0';
    return str;
}