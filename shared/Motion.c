#include "Motion.h"
#include "pwm.h"
#include <stdio.h>
#include "serial.h"
#include "RC_Servo.h"
#include "IO_Ports.h"

#define LEFT_MOTOR_EN_PIN PWM_PORTY12
#define RIGHT_MOTOR_EN_PIN PWM_PORTY10
#define LIFT_MOTOR_EN_PIN PWM_PORTX11

#define LEFT_MOTOR_DIR_PIN PIN11
#define RIGHT_MOTOR_DIR_PIN PIN9
#define LIFT_MOTOR_DIR_PIN PIN8

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LIFT_MOTOR 2

#define UP 0
#define DOWN 1

#define MOTOR_PORT PORTY

#define REN_DOOR_SERVO_PIN RC_PORTX03
#define BRIDGE_DOOR_SERVO_PIN RC_PORTX04
#define BRIDGE_SERVO_PIN RC_PORTY06

#define BRIDGE_UP 700
#define BRIDGE_DOWN 1800
#define BRIDGE_COMPACT 2500
#define BRIDGE_DOOR_OPEN 2000
#define BRIDGE_DOOR_CLOSED 1300
#define REN_DOOR_OPEN 1200
#define REN_DOOR_CLOSED 1600


//---------- Private Prototypes ----------//
void set_motor_direction(uint8_t motor, uint8_t direction);
void set_motor_speed(uint8_t motor, uint8_t speed);
uint8_t correct_speed(uint8_t speed);


void motion_init(void) {
    IO_PortsSetPortOutputs(MOTOR_PORT, LEFT_MOTOR_DIR_PIN);
    IO_PortsSetPortOutputs(MOTOR_PORT, RIGHT_MOTOR_DIR_PIN);
    IO_PortsSetPortOutputs(MOTOR_PORT, LIFT_MOTOR_DIR_PIN);
    
    PWM_Init();
    PWM_AddPins(LEFT_MOTOR_EN_PIN);
    PWM_AddPins(RIGHT_MOTOR_EN_PIN);
    PWM_AddPins(LIFT_MOTOR_EN_PIN);
    motion_stop();
    motion_stop_lift();
    
    RC_Init();
    RC_AddPins(REN_DOOR_SERVO_PIN);
    RC_AddPins(BRIDGE_DOOR_SERVO_PIN);
    RC_AddPins(BRIDGE_SERVO_PIN);
    motion_raise_bridge();
    motion_close_bridge_door();
    motion_close_ren_door();
}

void motion_move(uint8_t dir, uint8_t speed) {  
    set_motor_direction(LEFT_MOTOR, dir);
    set_motor_direction(RIGHT_MOTOR, dir);
    
    speed = correct_speed(speed);
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
    
    set_motor_speed(LEFT_MOTOR, 35);
    set_motor_speed(RIGHT_MOTOR, 35);
}

void motion_tank_right() {
    
    set_motor_direction(LEFT_MOTOR, FORWARD);
    set_motor_direction(RIGHT_MOTOR, REVERSE);
    
    set_motor_speed(LEFT_MOTOR, 35);
    set_motor_speed(RIGHT_MOTOR, 35);
}

void motion_bank_left(uint8_t dir) {
    
    set_motor_direction(LEFT_MOTOR, dir);
    set_motor_direction(RIGHT_MOTOR, dir);
     
    set_motor_speed(LEFT_MOTOR, 30);
    set_motor_speed(RIGHT_MOTOR, 50);
}

void motion_bank_right(uint8_t dir) {
    set_motor_direction(LEFT_MOTOR, dir);
    set_motor_direction(RIGHT_MOTOR, dir);
        
    set_motor_speed(LEFT_MOTOR, 50);
    set_motor_speed(RIGHT_MOTOR, 30);
}

void motion_pivot_left(uint8_t dir, uint8_t speed) {
    set_motor_speed(LEFT_MOTOR, 0);
    set_motor_direction(RIGHT_MOTOR, dir);
    
    set_motor_speed(RIGHT_MOTOR, correct_speed(speed));
}

void motion_pivot_right(uint8_t dir, uint8_t speed) {
    set_motor_speed(RIGHT_MOTOR, 0);
    set_motor_direction(LEFT_MOTOR, dir);
    
    set_motor_speed(LEFT_MOTOR, correct_speed(speed));
}

void motion_raise_lift(void) {
    set_motor_speed(LIFT_MOTOR, MAX_SPEED);
    set_motor_direction(LIFT_MOTOR, UP);
}

void motion_lower_lift(void) {
    set_motor_speed(LIFT_MOTOR, MAX_SPEED);
    set_motor_direction(LIFT_MOTOR, DOWN);
}

void motion_stop_lift(void) {
    set_motor_speed(LIFT_MOTOR, 0);
}



void motion_lower_bridge(void) {
    RC_SetPulseTime(BRIDGE_SERVO_PIN, BRIDGE_DOWN);
}

void motion_raise_bridge(void) {
    RC_SetPulseTime(BRIDGE_SERVO_PIN, BRIDGE_UP);
}

void motion_compact_bridge(void) {
    RC_SetPulseTime(BRIDGE_SERVO_PIN, BRIDGE_COMPACT);
}

void motion_open_bridge_door(void) {
    RC_SetPulseTime(BRIDGE_DOOR_SERVO_PIN, BRIDGE_DOOR_OPEN);
}

void motion_close_bridge_door(void) {
    RC_SetPulseTime(BRIDGE_DOOR_SERVO_PIN, BRIDGE_DOOR_CLOSED);
}

void motion_open_ren_door(void) {
    RC_SetPulseTime(REN_DOOR_SERVO_PIN, REN_DOOR_OPEN);
}

void motion_close_ren_door(void) {
    RC_SetPulseTime(REN_DOOR_SERVO_PIN, REN_DOOR_CLOSED);
}



void delay(void) {
    int i;
    for (i = 0; i < 1000000; i++);
}

//---------- Private Functions ----------//

void set_motor_direction(uint8_t motor, uint8_t direction) {
    uint16_t pin;
    if (motor == LEFT_MOTOR) {
        pin = LEFT_MOTOR_DIR_PIN;
    } else if (motor == RIGHT_MOTOR) {
        pin = RIGHT_MOTOR_DIR_PIN;
    } else {
        pin = LIFT_MOTOR_DIR_PIN;
    }
    
    if (direction == FORWARD && motor == LEFT_MOTOR) {
        IO_PortsSetPortBits(MOTOR_PORT, pin);
    } else if (direction == REVERSE && motor == LEFT_MOTOR) {
        IO_PortsClearPortBits(MOTOR_PORT, pin);
        
    } else if (direction == FORWARD && motor == RIGHT_MOTOR) {
        IO_PortsClearPortBits(MOTOR_PORT, pin);
    } else if (direction == REVERSE && motor == RIGHT_MOTOR) {
        IO_PortsSetPortBits(MOTOR_PORT, pin);
    }
    
    if (direction == UP && motor == LIFT_MOTOR) {
        IO_PortsClearPortBits(MOTOR_PORT, pin);
    } else if (direction == DOWN && motor == LIFT_MOTOR) {
        IO_PortsSetPortBits(MOTOR_PORT, pin);
    }
}

void set_motor_speed(uint8_t motor, uint8_t speed) {
    uint16_t pin;
    if (motor == LEFT_MOTOR) {
        pin = LEFT_MOTOR_EN_PIN;
    } else if (motor == RIGHT_MOTOR) {
        pin = RIGHT_MOTOR_EN_PIN;
    } else {
        pin = LIFT_MOTOR_EN_PIN;
    }
    PWM_SetDutyCycle(pin, speed * 10);
}

uint8_t correct_speed(uint8_t speed) {
    if (speed < MIN_SPEED) {
        return MIN_SPEED;
    } else if (speed > MAX_SPEED) {
        return MAX_SPEED;
    } else {
        return speed;
    }
}


//#define MOTION_TEST_HARNESS
#ifdef MOTION_TEST_HARNESS

void main(void) {
    BOARD_Init();
    printf("\r\nRunning motion test harness");
    motion_init();
    
//    while(1) {
//        motion_raise_lift();
//        printf("\r\nRaise Lift");
//        delay();
//        motion_lower_lift();
//        printf("\r\nLower Lift");
//        delay();
//        motion_stop_lift();
//        printf("\r\nStop Lift");
//        delay();
//    }
    
//    while(1) {
//        motion_open_bridge_door();
//        motion_open_ren_door();
//        motion_lower_bridge();
//        printf("\r\n Doors Open");
//        delay();
//        motion_close_bridge_door();
//        motion_close_ren_door();
//        motion_raise_bridge();
//        printf("\r\n Doors Closed");
//        delay();
//        motion_compact_bridge();
//        printf("\r\n Bridge Compacted");
//        delay();
//    }

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
        motion_pivot_left(FORWARD, MIN_SPEED);
        printf("\r\nPivot Left Forward");
        delay();
        motion_pivot_left(REVERSE, MIN_SPEED);
        printf("\r\nPivot Left Reverse");
        delay();
        motion_pivot_right(FORWARD, MIN_SPEED);
        printf("\r\nPivot Right Forward");
        delay();
        motion_pivot_right(REVERSE, MIN_SPEED);
        printf("\r\nPivot Right Reverse");
        delay();
        motion_stop();
        delay();
    }

}
#endif
