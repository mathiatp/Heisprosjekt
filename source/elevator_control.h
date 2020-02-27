/**
 * @file
 * @brief Functions used to controll the elevator. 
 */
#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include "hardware.h"
#include "timer.h"
#include "elevator_state.h"
#include "queue.h"


/**
 * @brief Sets the variable @p above_floor in the pointer @p p_elevator
 * @param p_elevator A pointer to an @p Elevator_state
 */
void elevator_control_set_above_floor(Elevator_state* p_elevator );


/**
 * @brief Sets the variables @p last_floor and @p on_floor in the pointer @p p_elevator
 * @param p_elevator A pointer to @p Elevator_state
 */
void elevator_control_set_elevator_floor(Elevator_state* p_elevator );


/**
 * @brief Controls the floor indicator lights
 * @param p_elevator A pointer to @p Elevator_state
 */
void elevator_control_set_floor_lights(Elevator_state* p_elevator);

/**
 * @brief   Clears all order lights. 
 * Downloaded from updated driver.
 */
void elevator_control_clear_all_order_lights();

/**
 * @brief Clears all order lights at @p floor 
 * @param floor Value of the floor.
 */
void elevator_control_clear_order_lights_at_floor(int floor);

/**
 * @brief  Initializes the elevator by clearing the @p queue and all order ligths, before it makes the elevator go down to ground floor.
 * @param p_elevator A pointer to an @p Elevator_state
 */
void elevator_control_init_elevator(Elevator_state* p_elevator);


/**
 * @brief Checks if the emergency stop button is pressed. If so: sets the @p state of @p p_elevator to @p EMERGENCY_STOP
 * @param p_elevator A pointer to @p Elevator_state
 */
void elevator_control_check_emergency_stop(Elevator_state* p_elevator);


/**
 * @brief Stops at @p floor
 * @param floor Value of the floor.
 * @return One when the elevator has stopped. Zero when not at floor. 
 */
int elevator_control_stop_at_floor(int floor);



/**
 * @brief Controlls the movement of the door.
 * Opens the door, before it closes after three seconds. 
 * If obstruction is activated the door will stay open until 3 seconds after obstruction is deactivated.
 * @return 0 when the door is open, 1 when the door is closed.
 */
int elevator_control_movement_door();

#endif
