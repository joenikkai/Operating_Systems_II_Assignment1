#include "pattern.h"

void test_free_extracted_strings(struct extracted_strings *es)
{
    if (!es)
    {
        printf("es is %p == null\n",es);
        return;
    }
    printf("es -> %p",es);
    free_extracted_strings(es);
}