#ifndef MOTION_H
#define MOTION_H

#include "BOARD.h"
#define FORWARD 1
#define REVERSE 0
#define LEFT_MOTOR_EN_PIN PWM_PORTY04
#define RIGHT_MOTOR_EN_PIN PWM_PORTY10

#define LEFT_MOTOR_DIR_PIN PIN3
#define RIGHT_MOTOR_DIR_PIN PIN9
#define MOTOR_PORT PORTY
#define BEEFY_PORT 


void motion_init();

void motion_move(uint8_t dir, uint8_t speed);

void motion_stop(void);

void motion_tank_left(void);

void motion_tank_right(void);

void motion_bank_left(uint8_t dir);

void motion_bank_right(uint8_t dir);

void motion_pivot_left(uint8_t dir);

void motion_pivot_right(uint8_t dir);


#endif //