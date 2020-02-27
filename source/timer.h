/**
 * @file
 * @brief Timer for opening the elevator door.
 *
 */

#ifndef TIMER_H
#define TIMER_H


#include <time.h>



/**
 * @brief Sets the time of when the timer starts.
 */
void timer_set_start_time();

/**
 * @brief Counts down 3 sec from start time 
 * @return 1 when 3 sec has passed, or 0 otherwise.
 */
int timer_door_countdown();

#endif
