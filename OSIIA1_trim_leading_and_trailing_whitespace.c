#include "main.h"

char *OSIIA1_trim_leading_and_trailing_whitespace(char *s)
{
    char *start = s;
    char *end = s + strlen(s) - 1;
    while (isspace((unsigned char)*start))
        start++;
    while (end > start && isspace((unsigned char)*end))
        end--;
    size_t len = end - start + 1;
    s[len] = '\0';
    return s;
}