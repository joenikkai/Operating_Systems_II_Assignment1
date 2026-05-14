#include "main.h"

char *OSIIA1_strn_to_lower(char *s, size_t l)
{
    if (s==NULL)
        return s;
    /* --- */
    char *new_s = calloc(l, sizeof(char));
    for (size_t i = 0; i < l; i++)
        new_s[i] = (char)tolower((unsigned char)s[i]);
    /* --- */
    return new_s;
}