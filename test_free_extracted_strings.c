#include "pattern.h"

void test_free_extracted_strings(struct extracted_strings *es)
{
    if (es)
        free(es);
}