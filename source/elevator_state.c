/**
 * @file
 * @brief Implementation file of elevator_state.h
 * 
 */

#include "elevator_state.h"
#include "hardware.h"

#define DIR_UP 1
#define DIR_DOWN 0

void elevator_state_set_above_floor(Elevator_state* p_elevator ){

    if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS-1)){
        p_elevator->above_floor = 0;
    }
    else if(hardware_read_floor_sensor(0)) {
        p_elevator->above_floor=1;
    }
    else if((hardware_read_floor_sensor(p_elevator->last_floor)) && (p_elevator->last_direction == DIR_UP)){
        p_elevator->above_floor = 1;
    }
    else if((hardware_read_floor_sensor(p_elevator->last_floor)) && (p_elevator->last_direction == DIR_DOWN)){
        p_elevator->above_floor = 0;
    }
    
}

void elevator_state_set_elevator_floor(Elevator_state* p_elevator){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        if(hardware_read_floor_sensor(floor)){
            p_elevator->last_floor = floor;
            p_elevator->on_floor = 1;
            break;
        }
        else{
            p_elevator->on_floor = 0;
        }
    }
}