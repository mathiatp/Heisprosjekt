#include "queue.h"
#include "heisstyring.h"
//#include "elevator_state.h"




int queue[NUM_OF_DIRECTIONS][NUM_OF_FLOORS];

void init_queue(){
    for (int dir=0; dir< NUM_OF_DIRECTIONS; dir++){
        for (int floor = 0;  floor<NUM_OF_FLOORS; floor++){
            queue[dir][floor]=0;
        }

    }
}

int check_queue(int direction){
    for (int floor = 0;  floor<NUM_OF_FLOORS; floor++){
        if(queue[direction][floor]==1){
            return floor+1;
        }
    }
    return 0;

    
}


void update_queue(struct memory_state*  elevator_state ){
for(int floor = 0;floor < NUM_OF_FLOORS;floor++){
    if(hardware_read_order(floor, HARDWARE_ORDER_INSIDE)){
        if(elevator_state->last_floor < floor+1){
            queue[1][floor] = 1;
        }
        else if(elevator_state->last_floor > floor+1){
            queue[0][floor] = 1;
        } //Hva skjer hvis det er ordre fra innsiden på denne etg.?
        
    }

    //if(hardware_read_order(floor, HARDWARE_ORDER_UP)){
        
    ;
}
}


int queue_is_empty(){
    if(!(check_queue(0)) && !(check_queue(1))){ 
        return 1;
    }
    return 0;
}