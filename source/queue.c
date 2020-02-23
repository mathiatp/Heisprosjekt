#include "queue.h"
#include "heisstyring.h"
#include "stdlib.h"
//#include "elevator_state.h"









void clear_queue(){
    for (int dir=0; dir< NUM_OF_DIRECTIONS; dir++){
        for (int floor = 0;  floor<NUM_OF_FLOORS; floor++){
            queue[dir][floor]=0;
        }

    }
}


int check_queue(int direction){

    
    for (int floor = 0;  floor < NUM_OF_FLOORS; floor++){

        if(queue[direction][floor]==1){
            return floor;
        }
    }


    for (int floor = 0;  floor < NUM_OF_FLOORS; floor++){
        if(queue[abs(direction-1)][floor]==1){
            return floor;
        }
    }

    return -1;

    
}

void delete_orders_from_floor(int floor){
    queue[0][floor] = 0;
    queue[1][floor] = 0;

    
    
}


void handle_orders(struct memory_state*  elevator_state ){
for(int floor = 0;floor < NUM_OF_FLOORS;floor++){
    if(hardware_read_order(floor, HARDWARE_ORDER_INSIDE)){
        hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE,1);
        if(elevator_state->last_floor < floor){
            queue[1][floor] = 1;
        }
        else if(elevator_state->last_floor > floor){
            queue[0][floor] = 1;
        } 
        else if((elevator_state->last_floor == floor) && (elevator_state->state == IDLE)){
            queue[0][floor] = 1;
            //queue[1][floor] = 1;
        }
        else{
            if(elevator_state->state == UP){
                queue[0][floor] = 1;
            }
            else if(elevator_state->state ==DOWN){
                queue[1][floor] = 1;
            }
            
        }
        
    }
    else if(hardware_read_order(floor, HARDWARE_ORDER_UP)){
        queue[1][floor] = 1;
        hardware_command_order_light(floor,HARDWARE_ORDER_UP,1);
        
    
    }
     else if(hardware_read_order(floor, HARDWARE_ORDER_DOWN)){
        queue[0][floor] = 1;
        hardware_command_order_light(floor,HARDWARE_ORDER_DOWN,1);
    
    }
}
}
//Brukes ikke 
/*int orders_above_floor(struct memory_state*  elevator_state ){
    for(int floor = elevator_state->last_floor; floor < NUM_OF_FLOORS-1; floor++ ){
        if(queue[1][floor]==1){
            return 1;
        }
    }
    return 0;  
}

int orders_below_floor(struct memory_state*  elevator_state ){
    for(int floor = elevator_state->last_floor; floor > NUM_OF_FLOORS-4; floor-- ){
        if(queue[1][floor]==1){
            return 1;
        }
    }
    return 0;  
}*/

int queue_is_empty(){
    if((0 > (check_queue(0))) && (0 > (check_queue(1)))){ 
        return 1;
    }
    return 0;
}