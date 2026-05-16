#include "OSIIA1_threads.h"
#include "jobs.h"

void push_new_job_instance(struct Job* j)
{
    if (!j)
        return;
    /* --- */
    
    /* create a new job instance  */
    struct job_instance* ji = calloc(1,sizeof(struct job_instance));
    ji->job_id = NUMBER_OF_JOBS++;
    
    ji->j = calloc(1,sizeof(struct Job));
    
    ji->j->arrival_time = j->arrival_time;
    ji->j->burst = j->burst;
    ji->j->e_code = j->e_code;

    if (!j->e_msg)
    {
        ji->j->e_msg = strdup("Custom Message [ No String Was Provided ].\n");
    }   
    else 
    {
        ji->j->e_msg = strdup(j->e_msg);
    }
    IN_BUCKET->ji[IN_BUCKET->ji_accummulation++] = ji;
}
