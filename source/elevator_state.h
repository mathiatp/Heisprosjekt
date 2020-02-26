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
} State;

/**
 * @brief   Struct for memorizing the state of the elevator,
 * @param last_floor Is zero indexed
 * @param last_direction Is zero when going down, and one when going up.
 * @param is_door_open Is zero when door is closed, and one when door is open.
 * @param in_floor Is one when in floor.
 * @param above_floor Is one when above floor, zero when under. 
 * @warning @p above_floor can be 1 while in_floor is one. Then the elevator is in a floor, not inbetween.
 */
typedef struct {
    State state;
    int last_floor;
    int last_direction; //0 is down, 1 is up
    int is_door_open; //0 = no, 1 = yes
    int in_floor; // 1 when in last_floor
    int above_floor;
}Elevator_state;

#endif
