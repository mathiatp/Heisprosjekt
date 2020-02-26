
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "elevator_control.h"


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




Elevator_state elevator = {IDLE, 0, 1, 0, 1, 0};

int main(){
    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    elevator_control_init_elevator(&elevator);

    printf("=== Elevator Program ===\n");
    printf("Press CTRL+C to stop program\n");
    
    
    
    while(1){
        signal(SIGINT, sigint_handler);
        elevator_control_set_elevator_floor(&elevator);
        elevator_control_set_above_floor(&elevator);
        queue_handle_orders(&elevator);
        elevator_control_check_emergency_stop(&elevator);

        
        switch(elevator.state){
            case IDLE:
                if(queue_is_empty(&elevator)){
                    elevator.state = IDLE;
                }
                else if(elevator.last_floor < queue_check(&elevator)){
                    elevator.state = UP;
                    break;
                }
                else if(elevator.last_floor > queue_check(&elevator)){
                    elevator.state = DOWN;
                    break;              
                }
                else if(hardware_read_floor_sensor(elevator.last_floor)){
                    elevator.state = DOOR_OPEN;
                    set_time_start();
                }
                else if(elevator.last_floor == queue_check(&elevator)){
                    if(elevator.above_floor == 1){
                        elevator.state = DOWN;
                    }
                    else if(elevator.above_floor == 0){
                        elevator.state = UP;
                    }
                }
                else{
                    printf("HER SKAL VI IKKE VÆRE");
                }
                break;
            case EMERGENCY_STOP:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator_control_clear_all_order_lights();


                while(hardware_read_stop_signal()){
                    queue_clear();
                    if(elevator.in_floor){
                        elevator_control_movement_door();
                    }
                }

                hardware_command_stop_light(0);
                if(elevator.in_floor){
                    elevator.state = DOOR_OPEN;
                    set_time_start();
                }
                else{
                    elevator.state = IDLE;
                    }
                break;
                
            case DOOR_OPEN:
                
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator.is_door_open = 1;
                elevator_control_clear_order_lights_at_floor(elevator.last_floor);
                
                if(elevator_control_movement_door()){
                    elevator.state = IDLE;
                    elevator.is_door_open = 0;
                    queue_delete_orders_from_floor(elevator.last_floor);
                }            
                break;
            case UP:
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                    elevator.last_direction = DIR_UP;
                    
                
                    if (elevator_control_stop_at_floor(queue_check(&elevator))){
                        elevator.state = DOOR_OPEN;
                        set_time_start();         
                    }       
                
                break;
            case DOWN:
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                elevator.last_direction = DIR_DOWN;
                
                                
                if (elevator_control_stop_at_floor(queue_check(&elevator))){
                    elevator.state = DOOR_OPEN;
                    set_time_start();         
                }    
               
                break;
            default:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator.state = IDLE;
                break;

        }
    }
    
}
