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
 * @brief   Struct for memorizing the state of the elevator,
 * @param last_floor Is zero indexed
 * @param last_direction Is zero when going down, and one when going up.
 * @param is_door_open Is zero when door is closed, and one when door is open.
 * @param on_floor Is one when in floor
 * @param above_floor Is one when above floor, zero when under. 
 * @warning @p above_floor can be one while @p on_floor is one. If so then the elevator is on a floor, not inbetween.
 */
typedef struct {
    FSM_STATE state;
    int last_floor;
    int last_direction;
    int is_door_open;
    int on_floor;
    int above_floor;
}Elevator_state;

#endif
