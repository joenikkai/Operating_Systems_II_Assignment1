#if !defined(OSIIA1_THREADS_H)
#define OSIIA1_THREADS_H

/**
 * constantly update window size.
 * manage the 3 buckets
 * - programs that have already run
 * - program that have been suspended
 * - programs that are incoming
 * The program that is currently running does not need a bucket because it is already in the VM's CPU
*/
#include <time.h>
#include <stdint.h>

#define MAXIMUM_IN_JI_ACCUMULATION ((uint16_t)(255)) /* incomming job instance accummulation */
#define MAXIMUM_OUT_JI_ACCUMULATION ((uint16_t)(1023)) /* outgoing job instance accummulation */
#define MAXIMUM_SUS_JI_ACCUMULATION ((uint16_t)(MAXIMUM_OUT_JI_ACCUMULATION - MAXIMUM_IN_JI_ACCUMULATION)) /* suspended job instance accummulation */

struct job_instance {
    uint8_t job_id;
    struct Job *j;
};

struct Bucket
{
    struct job_instance *ji;
    uint16_t ji_accummulation;
    uint16_t maximum_ji_accummulation;
};

extern struct Bucket *in_bucket; /* incoming processes */
extern struct Bucket *out_bucket; /* outgoing processes */
extern struct Bucket *sus_bucket; /* suspended but not finished processes */


#endif // OSIIA1_THREADS_H