#include "input.h"
#include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"

int main_program(int argc, char **argv)
{
    /* cpu thread */
    OSIIA1_thread_t execute_job_instance_thread;
    int execute_job_instance_thread_return_value = 0;

    /* handle user input thread */
    OSIIA1_thread_t handle_user_input_thread;
    int handle_user_input_thread_return_value = 0;
    int retval = 0;
    while (PROGRAM_IS_RUNNING)
    {
        /* start threads */
        /* handle user input  */
        execute_job_instance_thread_return_value = pthread_create(&execute_job_instance_thread,NULL,&execute_job_instance,NULL);
        if (execute_job_instance_thread_return_value!=0)
        {
            perror("pthread_create");
            return 1;
        }
        /* handle user input  */
        handle_user_input_thread_return_value = pthread_create(&handle_user_input_thread, NULL, &handle_user_input, NULL);
        if (handle_user_input_thread_return_value != 0)
        {
            perror("pthread_create");
            return 1;
        }

        /* --- join all threads --- */
        pthread_join(execute_job_instance_thread, NULL); /* job instance thread */
        pthread_join(handle_user_input_thread, NULL); /* handle input thread */
    }

    return retval;
}
