#include "Motion.h"
#include "pwm.h"
#include <stdio.h>
#include "serial.h"
#include "RC_Servo.h"
#include "IO_Ports.h"

#define LEFT_MOTOR_EN_PIN PWM_PORTY12
#define RIGHT_MOTOR_EN_PIN PWM_PORTY10

#define LEFT_MOTOR_DIR_PIN PIN11
#define RIGHT_MOTOR_DIR_PIN PIN9
#define MOTOR_PORT PORTY
#define BEEFY_PORT 


void motion_init(void) {
    PWM_Init();
    PWM_AddPins(LEFT_MOTOR_EN_PIN);
    PWM_AddPins(RIGHT_MOTOR_EN_PIN);
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 0);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 0);
    
    RC_Init();
    RC_AddPins(RC_PORTX03);
    RC_AddPins(RC_PORTX04);
    RC_AddPins(RC_PORTV04);
    
    IO_PortsSetPortOutputs(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
    IO_PortsSetPortOutputs(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
}

void motion_move(uint8_t dir, uint8_t speed) {
    if (speed > 100) {
        speed = 100;
    }
    if (dir == FORWARD) {
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
    } else {
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        
    }
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, speed * 10);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, speed * 10);
}

void motion_stop(void) {
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 0);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 0);
}

void motion_tank_left() {

    IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN | RIGHT_MOTOR_DIR_PIN);
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 1000);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 1000);
}

void motion_tank_right() {
    IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN | RIGHT_MOTOR_DIR_PIN);
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 1000);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 1000);
}

void motion_bank_left(uint8_t dir) {
    if (dir == FORWARD) {
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
    } else {
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        
    }
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 600);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 700);
}

void motion_bank_right(uint8_t dir) {
    if (dir == FORWARD) {
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
    } else {
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        
    }
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 700);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 600);
}

void motion_pivot_left(uint8_t dir) {
    if (dir == FORWARD) {
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
    } else {
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        
    }
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 0);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 600);
}

void motion_pivot_right(uint8_t dir) {
    if (dir == FORWARD) {
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
    } else {
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
        
    }
    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 600);
    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 0);
}

//void motion_beefy_up(void) {
//    RC_SetPulseTime(2000);
//}
//
//void motion_beefy_down(void) {
//    RC_SetPulseTime(1000);
//}
//
//void motion_ren_door_up(void) {
//    RC_SetPulseTime(2000);
//}
//
//void motion_ren_door_down(void) {
//    RC_SetPulseTime(1000);
//}
//
//void motion_track_door_up(void) {
//    RC_SetPulseTime(2000);
//}
//
//void motion_track_door_down(void) {
//    RC_SetPulseTime(1000);
//}

void delay(void) {
    int i;
    for (i = 0; i < 1000000; i++);
}


//#define MOTION_TEST_HARNESS
#ifdef MOTION_TEST_HARNESS

void main(void) {
    BOARD_Init();
    printf("Running motion test harness\r\n");
    motion_init();

    while (1) {
        motion_move(FORWARD, 100);
        delay();
        motion_move(REVERSE, 100);
        delay();
        motion_tank_left();
        delay();
        motion_tank_right();
        delay();
        motion_bank_left(FORWARD);
        delay();
        motion_bank_left(REVERSE);
        delay();
        motion_bank_right(FORWARD);
        delay();
        motion_bank_right(REVERSE);
        delay();
        motion_pivot_left(FORWARD);
        delay();
        motion_pivot_left(REVERSE);
        delay();
        motion_pivot_right(FORWARD);
        delay();
        motion_pivot_right(REVERSE);
        delay();
        motion_stop();
        delay();
    }

}
#endif
