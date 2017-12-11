#ifndef MOTION_H
#define MOTION_H

#include "BOARD.h"


#define FORWARD 1
#define REVERSE 0

#define MAX_SPEED 100
#define MIN_SPEED 21

#define RIGHT_NINETY_DEGREE_TURN_TICKS 700
#define LEFT_NINETY_DEGREE_TURN_TICKS 700

//----- Motor Control Functions -----//

void motion_init();

void motion_move(uint8_t dir, uint8_t speed);

void motion_stop(void);

void motion_tank_left();

void motion_tank_right();

void motion_bank_left(uint8_t dir);

void motion_bank_right(uint8_t dir);

void motion_pivot_left(uint8_t dir, uint8_t speed);

void motion_pivot_right(uint8_t dir, uint8_t speed);

void motion_raise_lift(void);

void motion_lower_lift(void);

void motion_stop_lift(void);


//----- Servo Control Functions -----//

void motion_lower_bridge(void);

void motion_raise_bridge(void);

void motion_open_bridge_door(void);

void motion_close_bridge_door(void);

void motion_open_ren_door(void);

void motion_close_ren_door(void);


#endif // MOTION_H //