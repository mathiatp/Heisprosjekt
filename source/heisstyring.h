#pragma once

#ifndef HEISSTYRING_H
#define HEISSTYRING_H

#include "hardware.h"
#include "timer.h"
#include "elevator_state.h"

void set_elevator_state_last_floor(struct memory_state*  elevator_state );
//void set_elevator_state_last_direction(struct memory_state*  elevator_state );
void check_emergency_stop(struct memory_state*  elevator_state);
int stop_at_floor(int floor);
int movement_door();
#endif