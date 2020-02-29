/**
 * @file
 * @brief Queue system for an elevator
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "elevator_state.h"
#include "hardware.h"

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
 * @param[in] p_elevator A pointer to an @p Elevator_state.
 * @return 1 if empty
 */
int queue_is_empty(Elevator_state* p_elevator);

/**
 * @brief Checks if there is an order in the @p queue. 
 * @param[in] p_elevator a pointer to an @p Elevator_state
 * @return the number of the floor of the next order
 * @warning returns -1 on empty queue.
 */
int queue_check(Elevator_state* p_elevator);


/**
 * @brief Deletes all orders in @p queue at a spesific @p floor.
 * @param[in] floor The floor to delete orders from.
 */
void queue_delete_orders_from_floor(int floor);


/**
 * @brief Adds a new order to the @p queue and turns on the order light
 * The function handles both orders from the inside and the outside of the elevator.
 * @param[in] p_elevator A pointer to an @p Elevator_state.
 */
void queue_add_order_and_set_order_light(Elevator_state* p_elevator);


#endif
