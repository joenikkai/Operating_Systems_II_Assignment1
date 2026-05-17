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
        
        // Each block is 6 characters wide: "+----+", then sharing the right pipe
        int block_width = 5; 
        int max_blocks = (w - 4) / block_width;
        int start_idx = (RECORDS_COUNT > max_blocks) ? RECORDS_COUNT - max_blocks : 0;
        int end_idx = RECORDS_COUNT;

        int x_offset = 2;
        long current_time = 0;
        
        // Calculate start time for the visible window
        for (int i = 0; i < start_idx; i++)
        {
            if (RECORDS[i]) current_time += RECORDS[i]->duration;
        }

        for (int i = start_idx; i < end_idx; i++)
        {
            if (RECORDS[i])
            {
                int x = x_offset + (i - start_idx) * block_width;
                
                // Top border
                mvwprintw(GRANTT_CHART_DISPLAY_WIN, 1, x, "+----+");
                
                // Remaining Burst (Rx)
                mvwprintw(GRANTT_CHART_DISPLAY_WIN, 2, x, "| R%-2d|", (int)RECORDS[i]->burst_time);
                
                // Process ID (Px)
                mvwprintw(GRANTT_CHART_DISPLAY_WIN, 3, x, "| P%-2d|", (int)RECORDS[i]->job_id);
                
                // Bottom border
                mvwprintw(GRANTT_CHART_DISPLAY_WIN, 4, x, "+----+");
                
                // Time markers
                mvwprintw(GRANTT_CHART_DISPLAY_WIN, 5, x, "%-2ld", current_time);
                current_time += RECORDS[i]->duration;
                if (i == end_idx - 1)
                {
                    mvwprintw(GRANTT_CHART_DISPLAY_WIN, 5, x + block_width, "%-2ld", current_time);
                }
            }
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
