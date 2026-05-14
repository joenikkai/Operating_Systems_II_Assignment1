#if !defined(TIMER_H)
#define TIMER_H

#include <stdio.h>
#include <time.h>

#if defined(__WIN32)
#include <windows.h>
#endif // __WIN32

/*
    We are going to use CPU time and not adjusted c time `time_t`.
    They are relatively the same if not adjusted.
*/

extern time_t time_quanta;
extern time_t starting_time;
extern time_t end_time_for_previous_job; /* might be the same as frequency */

/* OSIIA1 means Operating Systems II (Romanus 2) Assignment 1 */
static inline void OSIIA1_sleep(time_t time_quanta);
static inline void OSIIA1_millisecond_sleep(time_t time_quanta);
#endif // TIMER_H