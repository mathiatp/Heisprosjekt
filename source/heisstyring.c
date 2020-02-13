#include "heisstyring.h"


void set_floor_lights(int floor_sensor){
    hardware_command_floor_indicator_on(floor_sensor);
}

void stop_elevator_motor(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void stop_at_floor(int floor){
    if(hardware_read_floor_sensor(floor)){
        stop_elevator_motor();

    }
}

void open_door()