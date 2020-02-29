/**
 * @file
 * @brief Struct used to set the state of the elevator.
 * The state is further used to control the elevator.
 */

#ifndef ELEVATOR_STATE_H
#define ELEVATOR_STATE_H

/**
 * @brief   States used for FSM.
 */
typedef enum {
    IDLE,
    EMERGENCY_STOP,
    DOOR_OPEN,
    UP,
    DOWN
}FSM_STATE;

/**
 * @brief   Struct for memorizing the state of the elevator
 * @param last_floor Is zero indexed.
 * @param last_direction Is 0 when going down, 1 when going up.
 * @param is_door_open Is 0 when door is closed, 1 when door is open.
 * @param on_floor Is 1 when on floor.
 * @param above_floor Is 1 when above floor, 0 when under. 
 * @warning @p above_floor can be 1 while @p on_floor is 1. If so, the elevator is on a floor, not inbetween.
 */
typedef struct {
    FSM_STATE state;
    int last_floor;
    int last_direction;
    int is_door_open;
    int on_floor;
    int above_floor;
}Elevator_state;

/**
 * @brief Sets the variable @p above_floor in @p p_elevator
 * @param[in, out] p_elevator A pointer to an @p Elevator_state
 */
void elevator_state_set_above_floor(Elevator_state* p_elevator );


/**
 * @brief Sets the variables @p last_floor and @p on_floor in @p p_elevator
 * @param[in] p_elevator A pointer to @p Elevator_state
 */
void elevator_state_set_elevator_floor(Elevator_state* p_elevator );


#endif
