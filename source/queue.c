#include "queue.h"
#include "heisstyring.h"



int queue[NUM_OF_DIRECTIONS][NUM_OF_FLOORS];

void init_queue(){
    for (int dir=0; dir< NUM_OF_DIRECTIONS){
        for (int floor = 0;  floor<NUM_OF_FLOORS){
            direction[dir][floor]=0;
        }

    }
}

void check_queue(int direction){
    
    for (int floor = 0;  floor<NUM_OF_FLOORS){
        if(queue[direction][floor]==1){
            stop_at_floor(floor);
        }
        
    }

    
}