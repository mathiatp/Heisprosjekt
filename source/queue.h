
#ifndef QUEUE_H
#define QUEUE_H

#include "hardware.h"
#include "elevator_state.h"

#define NUM_OF_DIRECTIONS 2
#define DIR_UP 1
#define DIR_DOWN 0

int queue[NUM_OF_DIRECTIONS][HARDWARE_NUMBER_OF_FLOORS];

/**
 * @file
 * @brief Queuesystem for elevator
 *
 */

/**
 * @brief Clears all orders in @p queue by setting all values to 0.
 */
void queue_clear();

/**
 * @brief Checks if theres an order to any of the @p floors in a given @p direction 
 * @param direction Direction of the elevator
 * @return @p floor or -1 on empty queue.
 */
int queue_check(memory_state* elevator_state);

/**
 * @brief Clears all orders in @p queue at @p floor.
 * @param floor Which floor to delete orders from.
 */
void queue_delete_orders_from_floor(int floor);

/**
 * @brief Adds a new order to the queue
 * @param p_elevator_state A pointer to @p elevator_state.
 */

void queue_handle_orders(memory_state* elevator_state);

//BRUEKS DEN?
/**
 * @brief Checks if queue is empty
 * @return 1 if empty
 */
int queue_is_empty(memory_state* elevator_state);
#endif
