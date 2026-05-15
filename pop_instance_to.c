#include "OSIIA1_threads.h"
#include "jobs.h"

void pop_instance_to(void *src, void *dest)
{
    if (!src)
        return;
    struct Bucket *s = (struct Bucket *)src;
    struct Bucket *d = (struct Bucket *)dest;
    if (dest)
    {
        s->ji[s->ji_accummulation--] = d->ji[d->ji_accummulation++];
        return;
    }
    if (!s->ji[s->ji_accummulation--].j)
    {
        free_job(s->ji[s->ji_accummulation--].j);
    }
}