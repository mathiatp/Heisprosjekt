/**
 * @file
 * @brief Implementation file of queue.h
 * 
 */

#include "queue.h"

void queue_clear(){
    for (int dir = 0; dir < NUM_OF_DIRECTIONS; dir++){
        for (int floor = 0;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
            queue[dir][floor] = 0;
        }
    }
}

int queue_is_empty(Elevator_state* p_elevator){
    if(queue_check(p_elevator) == -1){ 
        return 1;
    }
    return 0;
}

int queue_check(Elevator_state* p_elevator){
    //Checks when we are inbetween floors and idle
    if((p_elevator->on_floor == 0) && (p_elevator->state == IDLE)){
        
        if(p_elevator->last_direction == DIR_DOWN){
            for (int floor = HARDWARE_NUMBER_OF_FLOORS - 1;  floor >= 0; floor--){
                if(queue[DIR_DOWN][floor] == 1){
                    return floor;
                }
            }
            for (int floor = 0 ;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
                if(queue[DIR_UP][floor] == 1){
                    return floor;
                }
            }
        }

        else if(p_elevator->last_direction == DIR_UP){
            
            for (int floor = 0 ;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
                if(queue[DIR_UP][floor] == 1){
                    return floor;
                }
            }
            for (int floor = HARDWARE_NUMBER_OF_FLOORS-1;  floor >= 0; floor--){
                if(queue[DIR_DOWN][floor] == 1){
                    return floor;
                }
            }            
        }
    }

    //Checks queue when last_dir = UP
    else if(p_elevator->last_direction == DIR_UP){

        for(int floor = p_elevator->last_floor;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
            if(queue[DIR_UP][floor] == 1){
                return floor;
            }
        }
        for (int floor = HARDWARE_NUMBER_OF_FLOORS - 1;  floor >= 0; floor--){
            if(queue[DIR_DOWN][floor] == 1){
                return floor;
            }
        }
        for(int floor = 0;  floor <= p_elevator->last_floor; floor++){
            if(queue[DIR_UP][floor] == 1){
                return floor;
            }
        }
    }

    //Checks queue when last_dir = DOWN
    else if(p_elevator->last_direction == DIR_DOWN){
        
        for (int floor = p_elevator->last_floor;  floor >= 0; floor--){
            if(queue[DIR_DOWN][floor] == 1){
                return floor;
            }
        }
        for (int floor = 0;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
            if(queue[DIR_UP][floor] == 1){
                return floor;
            }
        }
        for (int floor = HARDWARE_NUMBER_OF_FLOORS;  floor >= p_elevator->last_floor; floor--){
            if(queue[DIR_DOWN][floor] == 1){
                return floor;
            }
        }
    }
    return -1;
}

void queue_delete_orders_from_floor(int floor){
    queue[0][floor] = 0;
    queue[1][floor] = 0;    
}

void queue_add_order_and_set_order_light(Elevator_state* p_elevator ){
    for(int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){

        //Handles orders from inside the elevator
        if(hardware_read_order(floor, HARDWARE_ORDER_INSIDE)){
            hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE,1);

            if(p_elevator->last_floor < floor){
                queue[DIR_UP][floor] = 1;
            }
            else if(p_elevator->last_floor > floor){
                queue[DIR_DOWN][floor] = 1;
            }

            //If there is an ordere in the same floor as last_floor
            else if(p_elevator->last_floor == floor){
                if(p_elevator->state == IDLE){
                    queue[DIR_DOWN][floor] = 1;     //Queue does not care which direction of the queue the ordere is added to in this case. Chose down queue.
                }
                else if(p_elevator->state == DOOR_OPEN){
                    queue[DIR_DOWN][floor] = 1;     //Queue does not care which direction of the queue the ordere is added to in this case. Chose down queue.
                }
                else if(p_elevator->state == UP){
                    queue[DIR_DOWN][floor] = 1;
                }
                else if(p_elevator->state == DOWN){
                    queue[DIR_UP][floor] = 1;
                }                
            }            
        }


        //Handle orders from outside the elevator
        else if(hardware_read_order(floor, HARDWARE_ORDER_UP)){
            queue[1][floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
        }
        else if(hardware_read_order(floor, HARDWARE_ORDER_DOWN)){
            queue[0][floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
    }
}
