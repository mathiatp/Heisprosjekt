
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heisstyring.h"
#include "queue.h"
#include "timer.h"



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




struct memory_state elevator_state = {IDLE, 0, 1, 0, 1};

int main(){
    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    init_elevator(&elevator_state);

    printf("=== Elevator Program ===\n");
    printf("Press CTRL+C to stop program\n");
    
    
    
    while(1){
        signal(SIGINT, sigint_handler);
        set_elevator_state_last_floor(&elevator_state);
        handle_orders(&elevator_state);
        
        
        check_emergency_stop(&elevator_state);

        
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
                else if(hardware_read_floor_sensor(elevator_state.last_floor)){
                    elevator_state.state = DOOR_OPEN;
                    set_time_start();
                }
                else if(elevator_state.last_floor == check_queue(elevator_state.last_direction)){
                    if(elevator_state.last_direction == 1){
                        elevator_state.state = DOWN;
                    }
                    else{
                        elevator_state.state = UP;
                    }
                }
                else{
                    printf("HER SKAL VI IKKE VÆRE");
                }
                break;
            case EMERGENCY_STOP:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                clear_queue();
                clear_all_order_lights();

                while(hardware_read_stop_signal()){
                    //Leser ikke
                }

                if(elevator_state.is_door_open){
                    elevator_state.state = DOOR_OPEN;
                    set_time_start();
                }
                else{
                    elevator_state.state= IDLE;
                    }
                break;
                
            case DOOR_OPEN:
                
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator_state.is_door_open = 1;
                clear_order_lights_at_floor(elevator_state.last_floor);
                
                if(movement_door()){
                    elevator_state.state = IDLE;
                    elevator_state.is_door_open = 0;
                    delete_orders_from_floor(elevator_state.last_floor);
                }            
                break;
            case UP:
    
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                    elevator_state.last_direction = DIR_UP;
                    
                
                    if (stop_at_floor(check_queue(DIR_UP))){
                        elevator_state.state = DOOR_OPEN;
                        set_time_start();         
                    }       
                
                break;
            case DOWN:
             
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                elevator_state.last_direction = DIR_DOWN;
                
                                
                if (stop_at_floor(check_queue(DIR_DOWN))){
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
