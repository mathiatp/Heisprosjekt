#include "heisstyring.h"
#include "queue.h"
#include "stdio.h"



void set_elevator_state_last_floor(struct memory_state*  elevator_state ){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        if(hardware_read_floor_sensor(floor)){
            elevator_state->last_floor = floor;
        }
    }

    hardware_command_floor_indicator_on(elevator_state->last_floor);
}



void clear_all_order_lights(){
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

void clear_order_lights_at_floor(int floor){
    hardware_command_order_light(floor,HARDWARE_ORDER_UP,0);
    hardware_command_order_light(floor,HARDWARE_ORDER_DOWN,0);
    hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE,0);
}

void init_elevator(struct memory_state*  elevator_state){
       clear_all_order_lights();
       clear_queue();
       while(!(hardware_read_floor_sensor(0))){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
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


void check_emergency_stop(struct memory_state*  elevator_state){
    if(hardware_read_stop_signal()){
        elevator_state->state = EMERGENCY_STOP;
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

    
    if((hardware_read_obstruction_signal())){
        set_time_start(); //Finnes det noen bedre løsning?
        return 0;
        
    }
    else if(door_timer()){
        hardware_command_door_open(0);
        return 1;

    }
    return 0;
}

void out_of_bounds_safety(struct memory_state*  elevator_state){
    if((hardware_read_floor_sensor(3) || hardware_read_floor_sensor(0)) ){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        elevator_state->state = IDLE;
    }
}



