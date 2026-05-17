#include "input.h"
#include "timer.h"
#include "jobs.h"
#include "OSIIA1_threads.h"
#include "OSIIA1_terminal.h"

int main_program(int argc, char **argv)
{
    /* cpu thread */
    OSIIA1_thread_t execute_job_instance_thread;

    /* handle user input  */
    if ((pthread_create(&execute_job_instance_thread, NULL, &execute_job_instance, NULL)) != 0)
    {
        perror("pthread_create");
        return 1;
    }

    /* handle user input thread */
    OSIIA1_thread_t handle_user_input_thread;

    /* handle user input  */
    if ((pthread_create(&handle_user_input_thread, NULL, &handle_user_input, NULL)) != 0)
    {
        perror("pthread_create");
        return 1;
    }
    curs_set(0);

    while (PROGRAM_IS_RUNNING)
    {
        // The threads handle their own window updates
        // We only need to refresh the boxes if we want them to persist
        // but constant boxed refreshes will clear the scrolling content.
        // Let's just sleep to keep the main thread alive.
        OSIIA1_millisecond_sleep(100);
    }
    curs_set(1);

    /* --- join all threads --- */
    pthread_join(execute_job_instance_thread, NULL); /* job instance thread */
    pthread_join(handle_user_input_thread, NULL);    /* handle input thread */

    return 0;
}
