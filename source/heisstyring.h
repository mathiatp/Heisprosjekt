#pragma once

#ifndef HEISSTYRING_H
#define HEISSTYRING_H

#include "hardware.h"
#include "timer.h"
#include "elevator_state.h"

/**
 * @brief Sets the variable @p last_floor in the pointer @p elevator_state based on @p hardware_read_floor_sensor()
 * @param elevator_state A pointer to @p elevator_state
 */
void set_elevator_state_last_floor(struct memory_state*  elevator_state );

/**
 * @brief   Clears all orderlights. 
 * Downloaded form updated driver.
 */
void clear_all_order_lights();

/**
 * @brief Clears all orderelights at @p floor 
 * @param floor Value of the floor where an order was performed
 */
void clear_order_lights_at_floor(int floor);

/**
 * @brief  Initializeing the elevator by clearing alle order ligths and the @queue, before it makes the elevator go down to floor 1.
 * @param 
 */

//TRENGS PARAM?!
void init_elevator(struct memory_state*  elevator_state);

//void set_elevator_state_last_direction(struct memory_state*  elevator_state );

/**
 * @brief Checks if the emergency stop button is pressed. If so sets the @p state of @p elevator_state to @EMERGENCY_STOP.
 * @param elevator_state A pointer to @p elevator_state.
 */
void check_emergency_stop(struct memory_state*  elevator_state);

//SKAL DET VÆRE MED @HARDWARE OSV?
/**
 * @brief Stops at @floor when @p hardware_read_floor_sensor(floor) returns 1.
 * @param floor The floor the elevator will stop at.
 */
int stop_at_floor(int floor);

/**
 * @brief Opens the door, before it closes the door after a timer of three seconds end. If obstruction is activated the door will stay open
 * until obstruction is deactivated, and the timer of three seconds has run out.
 * @return 0 when the door is open, 1 when the door is closed.
 */
int movement_door();
void out_of_bounds_safety(struct memory_state*  elevator_state);

#endif
