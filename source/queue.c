#include "queue.h"
#include "elevator_control.h"
#include "stdlib.h"
//#include "elevator_state.h"



void queue_clear(){
    for (int dir=0; dir < NUM_OF_DIRECTIONS; dir++){
        for (int floor = 0;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
            queue[dir][floor] = 0;
        }

    }
}

    //Jeg tror det hele må endres her. Hvis vi legger til en state "above" som er lik null hvis den er i etasjen, og som setter lik 1 i state "UP"
    //vil vi kunne 
    //1. Hvis above==0, og ordre i etasjen, returnere etasjen for å åpne dør

    //2. Hvis vi beveger oss ned: iterere fra den etasjen vi er i og nedover. Først i nedkø, så i oppkø
    //2a. Hvis det da ikke er noe under iterer vi gjennom hele løkken (i riktig rekkefølge)

    //3. Hvis vi beveger oss opp: iterere fra den etasjen vi er i og oppover. Først i oppkø, så i nedkø
    //3a. Hvis det da ikke er noe under iterer vi gjennom hele løkken (i riktig rekkefølge)

int queue_check(memory_state* elevator_state){

    if (elevator_state->in_floor == 1){
        if(queue[0][elevator_state->last_floor] == 1){
            return elevator_state->last_floor;
        }

        else if(queue[1][elevator_state->last_floor] == 1){
            return elevator_state->last_floor;
        }
    }


    if(elevator_state->in_floor == 0){
        if(elevator_state->last_direction == 0){
            for (int floor = elevator_state->last_floor-1;  floor >= 0; floor--){
                if(queue[0][floor] == 1){
                    return floor;
                }
            }

            for (int floor = 0 ;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
                if(queue[1][floor] == 1){
                    return floor;
                }
            }
        }

        else if(elevator_state->last_direction == 1){
            for (int floor =elevator_state->last_floor+1 ;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
                if(queue[1][floor] == 1){
                    return floor;
                }
            }

            for (int floor = HARDWARE_NUMBER_OF_FLOORS-1;  floor >= 0; floor--){
                if(queue[0][floor] == 1){
                    return floor;
                }
            }
            
            
        }
    }

    for (int floor = 0;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){

        if(queue[elevator_state->last_direction][floor] == 1){
            return floor;
        }
    }


    for (int floor = 0;  floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        if(queue[abs(elevator_state->last_direction-1)][floor] == 1){
            return floor;
        }
    }

    return -1;

    
}

void queue_delete_orders_from_floor(int floor){
    queue[0][floor] = 0;
    queue[1][floor] = 0;

    
    
}


void queue_handle_orders(memory_state* elevator_state ){
    for(int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
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
            }
            else{ //Hvis du er mellom to etasjer. Brukes ved emergency stop
                if(elevator_state->state == UP){
                    queue[0][floor] = 1;
                }
                else if(elevator_state->state == DOWN){
                    queue[1][floor] = 1;
                }
                
            }
            
        }
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

int queue_is_empty(memory_state *elevator_state){
    if(queue_check(elevator_state) == -1){ 
        return 1;
    }
    return 0;
}