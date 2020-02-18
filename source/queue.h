#include "hardware.h"
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
 * @return Nothing.
 */
void check_queue(int direction); //Burde vi ha med hvilken etasje vi var i sist for bedre styring? Kanskje del av state?