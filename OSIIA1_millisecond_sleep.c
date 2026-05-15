#include "timer.h"

static inline void OSIIA1_millisecond_sleep(time_t time_quanta)
{

/**
 * \brief Sleep for a specified number of milliseconds.
 * \param milliseconds Time to sleep in milliseconds.
 */
#if defined(__WIN32) /* platform */
    Sleep(time_quanta);
#elif defined(__unix__)
    struct timespec ts;
    ts.tv_sec = time_quanta/1000;
    ts.tv_nsec = (time_quanta % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
#error PLATFORM_COMPATIBILITY_ERROR
#endif /* platform */
}