

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
 * @brief   Struct for memorizing the state of the elevator
 * @param last_floor Is one indexed
 * @param last_direction Is zero when going down, and one when going up.
 */
struct memory_state{
    State state;
    int last_floor;
    int last_direction; //0 is down, 1 is up
    int is_door_open; //0 = no, 1 = yes
};

//struct memory_state elevator_state = {IDLE, 1, 1};
#endif