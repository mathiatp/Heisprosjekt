/**
 * @file
 * @brief Queuesystem for elevator
 * 
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "elevator_control.h"

#define NUM_OF_DIRECTIONS 2 
#define DIR_UP 1
#define DIR_DOWN 0

int queue[NUM_OF_DIRECTIONS][HARDWARE_NUMBER_OF_FLOORS];



/**
 * @brief Clears all orders in @p queue by setting all values to 0.
 */
void queue_clear();

/**
 * @brief Checks if queue is empty
 * @param p_elevator A pointer to an @p Elevator_state.
 * @return 1 if empty
 */
int queue_is_empty(Elevator_state* elevator);

/**
 * @brief Checks if there is an order to any of the @p floors in a given @p direction
 * @param direction Direction of the elevator
 * @return the first @p floor with an order, or -1 on empty queue.
 */
int queue_check(Elevator_state* elevator);


/**
 * @brief Clears all orders in @p queue at a spesific @p floor.
 * @param floor The floor to delete orders from.
 */
void queue_delete_orders_from_floor(int floor);


/**
 * @brief Adds a new order to the queue
 * @param p_elevator A pointer to an @p Elevator_state.
 */
void queue_add_order_and_set_order_light(Elevator_state* elevator);


#endif
