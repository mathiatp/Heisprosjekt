#include "heisstyring.h"
#include "queue.h"
#include "stdio.h"



void set_elevator_state_last_floor(struct memory_state*  elevator_state ){
    for (int floor = 0; floor<HARDWARE_NUMBER_OF_FLOORS; floor++){
        if(hardware_read_floor_sensor(floor)){
            elevator_state->last_floor = floor;
        }
    }
    

    hardware_command_floor_indicator_on(elevator_state->last_floor);
}

/*void set_elevator_state_last_direction(struct memory_state*  elevator_state ){
    if(elevator_state->last_floor==0){
        elevator_state->last_direction=1;
    }
    else if(elevator_state->last_floor==3){
        elevator_state->last_direction=0;
    }
    else if(orders_above_floor(elevator_state)){
        elevator_state->last_direction = 0;
    }
    else if(orders_below_floor(elevator_state)){
        elevator_state->last_direction = 1;
    }
}*/


void emergency_stop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    if(!(hardware_read_stop_signal())){
        //change state
    }
}

int stop_at_floor(int floor){
    if(hardware_read_floor_sensor(floor)){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        return 1;
    }
    return 0;
}

int movement_door(){
    hardware_command_door_open(1);
    if(door_timer()){
        hardware_command_door_open(0);
        return 1;

    }
    //if(!(hardware_read_obstruction_signal())){
      //   hardware_command_door_open(0);
    //}
    
    return 0;
}