#include "OSIIA1_threads.h"

void free_bucket(struct Bucket *b)
{
    if (!b)
        return;
    /* --- */
    if (b->ji)
    {
        for (int i = 0; i < b->ji_accummulation; i++)
        {
            if (b->ji[i])
                free_job_instance(b->ji[i]);
        }
        free(b->ji);
    }
    free(b);
}
