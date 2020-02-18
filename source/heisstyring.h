#pragma once

#include "hardware.h"
#include "timer.h"

void set_floor_lights(int floor_sensor);
void stop_elevator_motor();
void emergency_stop();
void stop_at_floor(int floor);
void movement_door();