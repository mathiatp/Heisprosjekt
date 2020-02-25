
#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include "hardware.h"
#include "timer.h"
#include "elevator_state.h"

/**
 * @brief Sets the variable @p last_floor in the pointer @p p_elevator based on @p hardware_read_floor_sensor()
 * @param p_elevator A pointer to @p elevator
 */
void elevator_control_set_elevator_floor(Elevator_state* p_elevator );

/**
 * @brief   Clears all orderlights. 
 * Downloaded form updated driver.
 */
void elevator_control_clear_all_order_lights();

/**
 * @brief Clears all orderelights at @p floor 
 * @param floor Value of the floor where an order was performed
 */
void elevator_control_clear_order_lights_at_floor(int floor);

/**
 * @brief  Initializeing the elevator by clearing alle order ligths and the @queue, before it makes the elevator go down to floor 1.
 * @param 
 */

//TRENGS PARAM?!
void elevator_control_init_elevator(Elevator_state* p_elevator);


/**
 * @brief Checks if the emergency stop button is pressed. If so sets the @p state of @p p_elevator to @p EMERGENCY_STOP.
 * @param p_elevator A pointer to @p elevator.
 */
void elevator_control_check_emergency_stop(Elevator_state* p_elevator);

//SKAL DET VÆRE MED @HARDWARE OSV?
/**
 * @brief Stops at @p floor when @p hardware_read_floor_sensor(floor) returns 1.
 * @param floor The floor the elevator will stop at.
 */
int elevator_control_stop_at_floor(int floor);

/**
 * @brief Opens the door, before it closes the door after a timer of three seconds end. If obstruction is activated the door will stay open
 * until obstruction is deactivated, and then the timer of three seconds has run out.
 * @return 0 when the door is open, 1 when the door is closed.
 */
int elevator_control_movement_door();

#endif
