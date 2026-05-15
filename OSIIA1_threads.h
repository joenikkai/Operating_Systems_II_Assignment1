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

struct Bucket {
    int job_id;
    char *job_e_msg;
    time_t time_burst_time;
};

extern struct Bucket *in_bucket; /* incoming processes */
extern struct Bucket *out_bucket; /* completed processes */
extern struct Bucket *sus_bucket; /* suspended but not finished processes */

struct Bucket *in_bucket;
struct Bucket *out_bucket;
struct Bucket *sus_bucket;
#endif // OSIIA1_THREADS_H