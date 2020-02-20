

#include "timer.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>

clock_t start_time;

void set_time_start(){
    start_time=clock();
    
}


int door_timer(){
    int delay =3;

    clock_t now_time = clock();
    
    if(((now_time-start_time)/CLOCKS_PER_SEC) >= delay){
        return 1;
    }
    return 0;
}