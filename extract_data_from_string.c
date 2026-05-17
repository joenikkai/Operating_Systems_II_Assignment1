#include "OSIIA1_pattern.h"
#include <stdio.h>


struct extracted_strings *extract_data_from_string(char *s) /* extracts all regex groups and stores them in a struct containing the number of strings, the length of each string and the data of each string. includes the whole match.*/
{
    /* check for regex match */
    regmatch_t matches[_OSIIA1_PATTERN_GROUPS];
    if (regexec(&REGEX, s, _OSIIA1_PATTERN_GROUPS, matches, 0) != 0)
        return NULL; /* if no matches */
    
    /* new es obj */
    struct extracted_strings *es = calloc(1, sizeof(struct extracted_strings));
    es->number_of_groups = _OSIIA1_PATTERN_GROUPS;
    es->length_of_strings = calloc(es->number_of_groups, sizeof(size_t));
    es->strings = calloc(es->number_of_groups, sizeof(char *));

    /* loop over each group  */
    /* do not ignore the whole match */
    for (size_t i = 0; i < es->number_of_groups;i++)
    {
        size_t len = matches[i].rm_eo - matches[i].rm_so;
        char *i_es = calloc(len + 1, sizeof(char));
        snprintf(i_es,len+1,"%.*s",len,s+matches[i].rm_so);
        es->length_of_strings[i] = len;
        es->strings[i] = i_es;
    }
    return es;
}