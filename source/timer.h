#ifndef TIMER_H
#define TIMER_H


#include <time.h>

/**
 * @file
 * @brief Timer for opening the elevator door.
 *
 */

/**
 * @brief Sets the time of when the timer starts
 * @return Nothing.
 */
void set_time_start();

/**
 * @brief Counts down 3 sec from start time 
 * @return 1 when 3 sec has passed.
 */
int door_timer();

#endif
