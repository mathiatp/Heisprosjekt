/**
 * @file
 * @brief Implementation file of elevator_control.h
 * 
 */
#include "elevator_control.h"

void elevator_control_set_above_floor(Elevator_state* p_elevator ){

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

void elevator_control_set_elevator_floor(Elevator_state* p_elevator){
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


void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}



void elevator_control_set_floor_lights(Elevator_state* p_elevator){
    hardware_command_floor_indicator_on(p_elevator->last_floor);
}

void elevator_control_clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

void elevator_control_clear_order_lights_at_floor(int floor){
    hardware_command_order_light(floor,HARDWARE_ORDER_UP,0);
    hardware_command_order_light(floor,HARDWARE_ORDER_DOWN,0);
    hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE,0);
}

void elevator_control_init_elevator(){
    //Handout code---------------------------------------------
    signal(SIGINT, sigint_handler);
    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    //---------------------------------------------------------
    
    elevator_control_clear_all_order_lights();
    queue_clear();

    while(!(hardware_read_floor_sensor(0))){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void elevator_control_check_emergency_stop(Elevator_state* p_elevator){
    if(hardware_read_stop_signal()){
        p_elevator->state = EMERGENCY_STOP;
    }
    
}

int elevator_control_stop_at_floor(int floor){
    if(hardware_read_floor_sensor(floor)){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        return 1;
    }
    return 0;
}

int elevator_control_movement_door(){
    hardware_command_door_open(1);
    
    if(hardware_read_stop_signal()){
        return 0;
    }
    else if((hardware_read_obstruction_signal())){
        timer_set_start_time();
        return 0;
    }
    else if(timer_door_countdown()){
        hardware_command_door_open(0);
        return 1;
    }
    
    return 0;
}