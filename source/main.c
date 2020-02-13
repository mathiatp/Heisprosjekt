#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heisstyring.h"
#include "timer.h"



int main(){
    int floor;
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardware_command_movement(HARDWARE_MOVEMENT_UP);


       
    
    
     while(1){
         for(int i=0;i<4;i++){
             if((hardware_read_order(i,HARDWARE_ORDER_INSIDE))){
                 floor=i;
                 break;
             }
         }
        if(hardware_read_stop_signal()){
            stop_elevator_motor();
            break;
        }
        
        set_floor_lights(1);
        
        stop_at_floor(floor);

        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            
        }
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
    }
}
