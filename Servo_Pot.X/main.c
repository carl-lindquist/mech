/*
 * File:   main.c
 * Author: clindqui
 *
 * Created on October 1, 2017, 12:09 PM
 */


#include "xc.h"

#include <BOARD.h>
#include <stdio.h>
#include <AD.h>
#include <IO_Ports.h>
#include <RC_Servo.h>
#include <LED.h>

#include <timers.h>

#define NL "\r\n"
#define LED_ALL_BANKS (LED_BANK1 | LED_BANK2 | LED_BANK3)


//----- Helper Functions -----//
void RC_SetPosition(unsigned short int port, uint8_t pos) {
    unsigned short int pulse_modifier = (float)pos / 180.0 * (MAXPULSE - MINPULSE);
    RC_SetPulseTime(port, MINPULSE + pulse_modifier);
}

void LED_BarGraph(uint8_t leds_to_enable) {
    uint8_t i = 0;
    uint8_t leds = 0;
    while(i < 4 && i < leds_to_enable) {
        leds = (leds << 1) | 1;
        i++;
    }
    LED_SetBank(LED_BANK1, leds);
    leds = 0;
    while(i < 8 && i < leds_to_enable) {
        leds = (leds << 1) | 1;
        i++;
    }
    LED_SetBank(LED_BANK2, leds);
    leds = 0;
    while(i < 12 && i < leds_to_enable) {
        leds = (leds << 1) | 1;
        i++;
    }
    LED_SetBank(LED_BANK3, leds);
}


void msdelay(int time) {
    int zeropoint = TIMERS_GetTime();
    //printf("Requested time: %d Current time: %d\r\n", time, zeropoint);
    while ((TIMERS_GetTime() - zeropoint) < time){
        //printf("Current time: %d\r\n", TIMERS_GetTime());
    };
}

#define ADPORT AD_PORTV3
#define RCPORT RC_PORTV04

#define NORMAL

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    
    LED_Init();
    LED_AddBanks(LED_ALL_BANKS);
    
    AD_Init();
    AD_AddPins(ADPORT);
    
    RC_Init();
    RC_AddPins(RCPORT);
    
    uint8_t i = 0;
    uint16_t potval;
    
    while (1) {
#ifdef NORMAL
        //Normal code
        potval = AD_ReadADPin(ADPORT);
        if (potval > MINPULSE) {
            potval = MINPULSE;
        }
        // Lucky ducks with this scale we don't need to normalize
        RC_SetPulseTime(RCPORT, potval + MINPULSE);
        printf("Pulse Time: %d[uS]"NL, RC_GetPulseTime(RCPORT));
        msdelay(100);
#endif
#ifdef MINPULSETIME
        
        
        // Minimum Pulse Time test
        // Minimum pulse is a change in 10
        potval += 10;
        if (potval > 1000) {
            potval = 0;
        }
        RC_SetPulseTime(RCPORT, MINPULSE + (potval));
        printf("Pulse Time: %d[uS]"NL, RC_GetPulseTime(RCPORT));
        msdelay(500);
#endif
#ifdef ANGVELOCITY
        // Max range: 90 degrees
        // Measured: 360 ms fastest slew possible
        printf("ADC: %u[uS]"NL, AD_ReadADPin(ADPORT));
        RC_SetPulseTime(RCPORT, MINPULSE);
        msdelay(AD_ReadADPin(ADPORT));
        RC_SetPulseTime(RCPORT, MAXPULSE);
        msdelay(AD_ReadADPin(ADPORT));
        
#endif
#ifdef MINANGVELOCITY
        // Semi smooth at like 100ms
        // Fully smooth at around 20 ms
        potval += 10;
        if (potval > 1000) {
            potval = 0;
        }
        RC_SetPulseTime(RCPORT, MINPULSE + (potval));
        printf("ADC (Delay): %u[mS]"NL, AD_ReadADPin(ADPORT)>>2);
        msdelay(AD_ReadADPin(ADPORT)>>2);
        
#endif 
        LED_BarGraph( (int)((float)AD_ReadADPin(ADPORT) * 12.0 / MINPULSE) );
    }
}
