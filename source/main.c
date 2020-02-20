
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heisstyring.h"

#include "queue.h"
#include "timer.h"

/**
 * @brief   Clears all orderlights. 
 * Downloaded form updated driver.
 */
/*static void clear_all_order_lights(){
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
}*/

/**
 * @brief   Stops motort when ^C is pressed.
 * Downloaded form updated driver.
 */
static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}




struct memory_state elevator_state = {IDLE, 0, 1};

int main(){
    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    init_queue();

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    
    
    signal(SIGINT, sigint_handler);
    while(1){

        add_to_queue(&elevator_state);
        set_elevator_state_last_floor(&elevator_state);
        

        
        switch(elevator_state.state){
            case IDLE:
                if(queue_is_empty()){
                    elevator_state.state = IDLE;
                }
                else if(elevator_state.last_floor < check_queue(elevator_state.last_direction)){
                    elevator_state.state = UP;
                    break;
                }
                else if(elevator_state.last_floor > check_queue(elevator_state.last_direction)){
                    elevator_state.state = DOWN;
                    break;              
                }
                else{
                    elevator_state.state = DOOR_OPEN;
                    set_time_start();
                }
                break;
            case EMERGENCY_STOP:
                break;
            case DOOR_OPEN:
                delete_orders_from_floor(elevator_state.last_floor);
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                if(movement_door()){
                    elevator_state.state = IDLE;
                    
                }
                              
                break;
            case UP:
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
                elevator_state.last_direction = 1;
                 if (stop_at_floor(check_queue(1))){
                    elevator_state.state = DOOR_OPEN;
                    set_time_start();         
                }       
                break;
            case DOWN:
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                elevator_state.last_direction = 0;
                
                if (stop_at_floor(check_queue(0))){
                    elevator_state.state = DOOR_OPEN;
                    set_time_start();         
                }       
                break;
            default:
                if(queue_is_empty()){
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                }
                break;

        }
    }
    
}
