#include "timer.h"


/**
 * \brief Sleep for a specified number of milliseconds.
 * \param milliseconds Time to sleep in milliseconds.
 */
void OSIIA1_sleep(time_t time_quanta)
{
    OSIIA1_millisecond_sleep(time_quanta * 1000);
}
