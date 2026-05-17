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
        pthread_mutex_lock(&TERMINAL_MUTEX);
        pthread_mutex_lock(&BUCKET_MUTEX);
        
        werase(GRANTT_CHART_DISPLAY_WIN);
        box(GRANTT_CHART_DISPLAY_WIN, 0, 0);
        mvwprintw(GRANTT_CHART_DISPLAY_WIN, 0, 2, " GANTT CHART (SRTF) ");

        int h, w;
        getmaxyx(GRANTT_CHART_DISPLAY_WIN, h, w);
        int max_visible = w - 4;
        int start_idx = (RECORDS_COUNT > max_visible) ? RECORDS_COUNT - max_visible : 0;

        for (int i = start_idx; i < RECORDS_COUNT; i++)
        {
            if (RECORDS[i])
            {
                // Each job ID is mapped to a character or just the ID hex
                mvwaddch(GRANTT_CHART_DISPLAY_WIN, 2, 2 + (i - start_idx), (RECORDS[i]->job_id % 26) + 'A');
                mvwaddch(GRANTT_CHART_DISPLAY_WIN, 3, 2 + (i - start_idx), '|');
            }
        }
        
        if (RECORDS_COUNT > 0)
        {
             mvwprintw(GRANTT_CHART_DISPLAY_WIN, 5, 2, "Legend: A=1, B=2... (Job ID %% 26)");
        }

        wrefresh(GRANTT_CHART_DISPLAY_WIN);
        
        pthread_mutex_unlock(&BUCKET_MUTEX);
        pthread_mutex_unlock(&TERMINAL_MUTEX);

        OSIIA1_millisecond_sleep(500);
    }
    curs_set(1);

    /* --- join all threads --- */
    pthread_join(execute_job_instance_thread, NULL); /* job instance thread */
    pthread_join(handle_user_input_thread, NULL);    /* handle input thread */

    return 0;
}
