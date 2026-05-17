#include "main.h"
#include <string.h>
#include <ctype.h>

char *OSIIA1_trim_leading_and_trailing_whitespace(char *s)
{
    if (!s) return NULL;
    char *start = s;
    while (isspace((unsigned char)*start))
        start++;

    if (*start == '\0') {
        *s = '\0';
        return s;
    }

    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';

    // Move the trimmed string to the beginning of s
    if (start != s) {
        memmove(s, start, (end - start + 2));
    }

    return s;
}
