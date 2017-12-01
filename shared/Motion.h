#ifndef MOTION_H
#define MOTION_H

#include "BOARD.h"
#define FORWARD 1
#define REVERSE 0

#define MAX_SPEED 100
#define MIN_SPEED 30


void motion_init();

void motion_move(uint8_t dir, uint8_t speed);

void motion_stop(void);

void motion_tank_left();

void motion_tank_right();

void motion_bank_left(uint8_t dir);

void motion_bank_right(uint8_t dir);

void motion_pivot_left(uint8_t dir, uint8_t speed);

void motion_pivot_right(uint8_t dir, uint8_t speed);


#endif //