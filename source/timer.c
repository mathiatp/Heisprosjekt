

#include "timer.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>

clock_t start_time;

void timer_set_start_time(){
    start_time=clock();
}


int timer_door_countdown(){

    clock_t now_time = clock();
    int countdown_value =3;
    
    if(((now_time-start_time)/CLOCKS_PER_SEC) >= countdown_value){
        return 1;
    }

    return 0;
}