#include "timer.h"


#if defined(__WIN32) /* platform */
/**
 * \brief Sleep for a specified number of milliseconds.
 * \param milliseconds Time to sleep in milliseconds.
 */

static inline void OSIIA1_millisecond_sleep(time_t time_quanta)
{
    Sleep(time_quanta);
}
#elif defined(__unix__)
/**
 * \brief Sleep for a specified number of milliseconds.
 * \param milliseconds Time to sleep in milliseconds.
 */
static inline void OSIIA1_millisecond_sleep(time_t time_quanta)
{
    struct timespec ts;
    ts.tv_sec = time_quanta/1000;
    ts.tv_nsec = (time_quanta % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
#else
#error "This code might not work in your platform please implemement the code for your secific os and push it to us."
#endif /* platform */
