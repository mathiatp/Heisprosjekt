
#ifndef QUEUE_H
#define QUEUE_H

#include "hardware.h"
#include "elevator_state.h"
#define NUM_OF_FLOORS 4
#define NUM_OF_DIRECTIONS 2
#define DIR_UP 1
#define DIR_DOWN 0

int queue[NUM_OF_DIRECTIONS][NUM_OF_FLOORS];

/**
 * @file
 * @brief Queuesystem for elevator
 *
 */

/**
 * @brief Clears all orders in @p queue by setting all values to 0.
 */
void clear_queue();

/**
 * @brief Checks if theres an order to any of the floors in a given @p direction 
 * @param direction Direction of the elevator
 * @return floor or -1 on empty queue.
 */
int check_queue(int direction);

/**
 * @brief Clears all orders in @p queue at @p floor.
 * @param floor Which floor to delete orders from.
 */
void delete_orders_from_floor(int floor);

/**
 * @brief Adds a new order to the queue
 * @param elevator_state A pointer to elevator_state.
 */

void handle_orders(struct memory_state*  elevator_state);

//BRUKES IKKE
int orders_above_floor(struct memory_state*  elevator_state );
//BRUKES IKKE
int orders_below_floor(struct memory_state*  elevator_state );

//BRUEKS DEN?
/**
 * @brief Checks if queue is empty
 * @return 1 if empty
 */
int queue_is_empty();
#endif
