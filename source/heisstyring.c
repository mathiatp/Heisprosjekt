#include "heisstyring.h"



void set_floor_lights(int floor_sensor){
    hardware_command_floor_indicator_on(floor_sensor);
}

void stop_elevator_motor(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void emergency_stop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    if(!(hardware_read_stop_signal)){
        //change state
    }
}

void stop_at_floor(int floor){
    if(hardware_read_floor_sensor(floor)){
        stop_elevator_motor();
        movement_door();

    }
}

void movement_door(){
    hardware_command_door_open(1);
    set_time_start();
    //if(!(hardware_read_obstruction_signal())){
      //   hardware_command_door_open(0);
    //}
    hardware_command_door_open(0);
}