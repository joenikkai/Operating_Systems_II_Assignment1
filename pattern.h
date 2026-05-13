#if !defined(PATTERN_H)
#define PATTERN_H

#include <regex.h>
#include <stdlib.h>
#include "main.h"

extern int RET;
extern regex_t REGEX;
/* regex pattern */
#define UINT8_T__PATTERN "(25[0-5]|2[0-4][0-4]|[0-1]?[0-9]?[0-9])"
#define PATTERN "^[[:space:]]+"UINT8_T__PATTERN"[[:space:]]+\"([^\"]+)\"[[:space:]]+"UINT8_T__PATTERN"[[:space:]]+$"
#define PATTERN_GROUPS 4

/*
matches == 4
0 -> entire group
1 -> uint8_t
2 -> string
3 -> uint8_t
*/

struct extracted_strings
{
    size_t number_of_groups;
    size_t *length_of_strings;
    char **strings;
};

struct extracted_strings *extract_data_from_string(char *s);
void free_extracted_strings(struct extracted_strings *es);
#endif // PATTERN_H