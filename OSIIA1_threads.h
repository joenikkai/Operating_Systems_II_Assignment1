#if !defined(OSIIA1_THREADS_H)
#define OSIIA1_THREADS_H
#include "main.h"


#include <unistd.h>
#include <pthread.h>
typedef pthread_t OSIIA1_thread_t;
#define THREAD_RETURN void*
#define THREAD_RETURN_VALUE NULL



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
#define MAXIMUM_SUS_JI_ACCUMULATION ((uint16_t)(1023)) /* suspended job instance accummulation */

struct job_instance {
    uint16_t job_id;
    struct Job *j;
};

struct Bucket
{
    struct job_instance **ji;
    volatile uint16_t ji_accummulation;
    uint16_t maximum_ji_accummulation;
};

struct job_instance_record {
    uint16_t job_id;
    char *message;
    time_t burst_time;
};

extern struct Bucket *IN_BUCKET; /* outgoing processes */
extern struct Bucket *SUS_BUCKET; /* suspended but not finished processes */

extern volatile uint16_t NUMBER_OF_JOBS;
extern volatile uint16_t CPU_IS_EXECUTING;

extern struct job_instance *CURRENT_JOB; /* this is basically the register */

void free_job_instance(struct job_instance *ji);
void free_bucket(struct Bucket *b);

void *handle_user_input(void *arg); /* will contain everything that the main program has now `That is the input loop`*/
struct job_instance *extract_job_instance(struct job_instance *ji);
struct job_instance *load_job_instance(struct job_instance *ji);
void *execute_job_instance(void *arg); /* should not pass in anything is should find a loaded register */

/**
 * Add ways to 
 * - load 
 * - sort
 * - search
 * - and other vital info
 */

#endif // OSIIA1_THREADS_H
