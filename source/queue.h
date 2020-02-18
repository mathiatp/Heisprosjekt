
#ifndef QUEUE_H
#define QUEUE_H

#include "hardware.h"
#include "elevator_state.h"
#define NUM_OF_FLOORS 4
#define NUM_OF_DIRECTIONS 2

/**
 * @file
 * @brief Queuesystem for elevator
 *
 */

/**
 * @brief Initializes the queuesystem. 
 * @return Nothing.
 */
void init_queue();

/**
 * @brief Checks if theres an order to any of the floors in a given @p direction 
 * @param direction Direction of the elevator
 * @return floor. 
 * @warning @p floor is 1 indexed.
 */
int check_queue(int direction);

/**
 * @brief Updates the queue with a new order
 */

void update_queue(struct memory_state*  elevator_state);

/**
 * @brief Checks if queue is empty
 * @return 1 if empty
 */
int queue_is_empty();
#endif