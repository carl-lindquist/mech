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

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

#define MOTOR_PORT PORTY
#define BEEFY_PORT 


//---------- Private Prototypes ----------//
void set_motor_direction(uint8_t motor, uint8_t direction);
void set_motor_speed(uint8_t motor, uint8_t speed);


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
    
    set_motor_direction(LEFT_MOTOR, dir);
    set_motor_direction(RIGHT_MOTOR, dir);
    
    set_motor_speed(LEFT_MOTOR, speed);
    set_motor_speed(RIGHT_MOTOR, speed);
}

void motion_stop(void) {
    
    set_motor_speed(LEFT_MOTOR, 0);
    set_motor_speed(RIGHT_MOTOR, 0);
}

void motion_tank_left() {
    
    set_motor_direction(LEFT_MOTOR, REVERSE);
    set_motor_direction(RIGHT_MOTOR, FORWARD);
    
    set_motor_speed(LEFT_MOTOR, 100);
    set_motor_speed(RIGHT_MOTOR, 100);
}

void motion_tank_right() {
    
    set_motor_direction(LEFT_MOTOR, FORWARD);
    set_motor_direction(RIGHT_MOTOR, REVERSE);
    
    set_motor_speed(LEFT_MOTOR, 100);
    set_motor_speed(RIGHT_MOTOR, 100);
}

void motion_bank_left(uint8_t dir) {
    
    set_motor_direction(LEFT_MOTOR, dir);
    set_motor_direction(RIGHT_MOTOR, dir);
    
    set_motor_speed(LEFT_MOTOR, 60);
    set_motor_speed(RIGHT_MOTOR, 100);
}

void motion_bank_right(uint8_t dir) {
    set_motor_direction(LEFT_MOTOR, dir);
    set_motor_direction(RIGHT_MOTOR, dir);
    
    set_motor_speed(LEFT_MOTOR, 100);
    set_motor_speed(RIGHT_MOTOR, 60);
}

void motion_pivot_left(uint8_t dir) {
    set_motor_direction(RIGHT_MOTOR, dir);
    
    set_motor_speed(LEFT_MOTOR, 0);
    set_motor_speed(RIGHT_MOTOR, 60);
    
//    if (dir == REVERSE) {
//        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
//        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
//    } else {
//        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
//        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
//        
//    }
//    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 0);
//    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 600);
}

void motion_pivot_right(uint8_t dir) {
    set_motor_direction(LEFT_MOTOR, dir);
    
    set_motor_speed(LEFT_MOTOR, 60);
    set_motor_speed(RIGHT_MOTOR, 0);
    
//    if (dir == REVERSE) {
//        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
//        IO_PortsClearPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
//    } else {
//        IO_PortsSetPortBits(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
//        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
//        
//    }
//    PWM_SetDutyCycle(LEFT_MOTOR_EN_PIN, 600);
//    PWM_SetDutyCycle(RIGHT_MOTOR_EN_PIN, 0);
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
    for (i = 0; i < 8000000; i++);
}

//---------- Private Functions ----------//

void set_motor_direction(uint8_t motor, uint8_t direction) {
    uint16_t pin = (motor == LEFT_MOTOR ? LEFT_MOTOR_DIR_PIN : RIGHT_MOTOR_DIR_PIN);
    
    if (direction == FORWARD && motor == LEFT_MOTOR) {
        IO_PortsSetPortBits(MOTOR_PORT, pin);
    } else if (direction == REVERSE && motor == LEFT_MOTOR) {
        IO_PortsClearPortBits(MOTOR_PORT, pin);
        
    } else if (direction == FORWARD && motor == RIGHT_MOTOR) {
        IO_PortsClearPortBits(MOTOR_PORT, pin);
    } else if (direction == REVERSE && motor == RIGHT_MOTOR) {
        IO_PortsSetPortBits(MOTOR_PORT, pin);
    }
}

void set_motor_speed(uint8_t motor, uint8_t speed) {
    if (speed > 100) { // cap max speed
        speed = 100;
    }
    uint16_t pin = (motor == LEFT_MOTOR ? LEFT_MOTOR_EN_PIN : RIGHT_MOTOR_EN_PIN);
    PWM_SetDutyCycle(pin, speed * 10);
}


//#define MOTION_TEST_HARNESS
#ifdef MOTION_TEST_HARNESS

void main(void) {
    BOARD_Init();
    printf("Running motion test harness\r\n");
    motion_init();

    while (1) {
        motion_move(FORWARD, 100);
        printf("\r\nForward");
        delay();
        motion_move(REVERSE, 100);
        printf("\r\nReverse");
        delay();
        motion_tank_left();
        printf("\r\nTank Left");
        delay();
        motion_tank_right();
        printf("\r\nTank Right");
        delay();
        motion_bank_left(FORWARD);
        printf("\r\nBank Left Forward");
        delay();
        motion_bank_left(REVERSE);
        printf("\r\nBank Left Reverse");
        delay();
        motion_bank_right(FORWARD);
        printf("\r\nBank Right Forward");
        delay();
        motion_bank_right(REVERSE);
        printf("\r\nBank Right Reverse");
        delay();
        motion_pivot_left(FORWARD);
        printf("\r\nPivot Left Forward");
        delay();
        motion_pivot_left(REVERSE);
        printf("\r\nPivot Left Reverse");
        delay();
        motion_pivot_right(FORWARD);
        printf("\r\nPivot Right Forward");
        delay();
        motion_pivot_right(REVERSE);
        printf("\r\nPivot Right Reverse");
        delay();
        motion_stop();
        delay();
    }

}
#endif
