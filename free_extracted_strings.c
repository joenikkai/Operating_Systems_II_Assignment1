#include "OSIIA1_pattern.h"

void free_extracted_strings(struct extracted_strings *es) /* \brief frees the es struct \deprecated if not written tests for*/
{
    if (!es)
        return;
    for (size_t i = 0; i < es->number_of_groups; i++)
    {
        if (es->strings[i])
            free(es->strings[i]);
        /* --- */
    }

    if (es->length_of_strings)
        free(es->length_of_strings);
    /* --- */

    if (es->strings)
        free(es->strings);
    /* --- */
    if (es)
        free(es);
    /*---*/
}
