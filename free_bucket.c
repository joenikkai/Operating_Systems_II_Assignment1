#include "OSIIA1_threads.h"

void free_bucket(struct Bucket *b)
{
    if (!b)
        return;
    /* --- */
    free(b);
}
