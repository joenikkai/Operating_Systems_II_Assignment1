#include "timer.h"

#if defined(__WIN32) /* platform */
/**
 * \brief Sleep for a specified number of milliseconds.
 * \param milliseconds Time to sleep in milliseconds.
 */
static inline void OSIIA1_sleep(time_t time_quanta)
{
    OSIIA1_millisecond_sleep(time_quanta);
}
#elif defined(__unix__)
/**
 * \brief Sleep for a specified number of milliseconds.
 * \param milliseconds Time to sleep in milliseconds.
 */
static inline void OSIIA1_sleep(time_t time_quanta)
{
    OSIIA1_millisecond_sleep(time_quanta * 1000);
}
#else
#error "This code might not work in your platform please implemement the code for your secific os and push it to us."
#endif /* platform */
