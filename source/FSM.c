/**
 * @file
 * @brief Controls the FSM of the elevator.
 * Contains main()
 * 
 */
#include "elevator_control.h"

Elevator_state elevator = {IDLE, 0, 1, 0, 1, 0};

int main(){

    printf("=== Elevator Program ===\n");
    printf("Press CTRL+C to stop program\n");
    
    elevator_control_init_elevator();
    
    while(1){
        //Continious check-functions------------------------------------
        signal(SIGINT, sigint_handler);
        elevator_control_check_emergency_stop(&elevator);
        elevator_state_set_above_floor(&elevator);
        elevator_state_set_elevator_floor(&elevator);
        elevator_control_set_floor_lights(&elevator);
        queue_add_order_and_set_order_light(&elevator);
        //--------------------------------------------------------------     

        switch(elevator.state){
            case IDLE:
                if(queue_is_empty(&elevator)){
                    elevator.state = IDLE;                    
                }
                else if(elevator.last_floor < queue_check(&elevator)){
                    elevator.state = UP;
                }
                else if(elevator.last_floor > queue_check(&elevator)){
                    elevator.state = DOWN;           
                }
                else if(elevator.last_floor == queue_check(&elevator)){
                    if(elevator.on_floor){
                        elevator.state = DOOR_OPEN;
                        timer_set_start_time();
                    }
                    else if(elevator.above_floor == 1){
                        elevator.state = DOWN;
                    }
                    else if(elevator.above_floor == 0){
                        elevator.state = UP;
                    }
                }
                break;
                
            case EMERGENCY_STOP:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator_control_clear_all_order_lights();
                hardware_command_stop_light(1);

                while(hardware_read_stop_signal()){
                    queue_clear();
                    if(elevator.on_floor){
                        elevator_control_movement_door();
                    }
                }
                hardware_command_stop_light(0);

                if(elevator.on_floor){
                    elevator.state = DOOR_OPEN;
                    timer_set_start_time();
                }
                else{
                    elevator.state = IDLE;
                    }
                break;
                
            case DOOR_OPEN:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator.is_door_open = 1;       

                if(queue_check(&elevator) == elevator.last_floor){  //If an order is placed on the same floor to hold the door open
                    timer_set_start_time();
                }

                queue_delete_orders_from_floor(elevator.last_floor);
                elevator_control_clear_order_lights_at_floor(elevator.last_floor);

                
                if(elevator_control_movement_door()){
                    elevator.is_door_open = 0;
                    elevator.state = IDLE;
                }            
                break;

            case UP:
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                    elevator.last_direction = DIR_UP;
                    
                    if (elevator_control_stop_at_floor(queue_check(&elevator))){
                        elevator.state = DOOR_OPEN;
                        timer_set_start_time();        
                    }
                break;
                
            case DOWN:
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                elevator.last_direction = DIR_DOWN;
                               
                if (elevator_control_stop_at_floor(queue_check(&elevator))){
                    elevator.state = DOOR_OPEN;
                    timer_set_start_time();                             
                }    
                break;

            default:
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                elevator.state = IDLE;
                break;

        }
    }
    
}
