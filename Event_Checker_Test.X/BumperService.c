/*
 * File: TapeSensorService.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeSensorService.h"
#include <stdio.h>
#include "IO_Ports.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define SERVICE_TIMER_TICKS 100

#define BUMPER_PORT PORTZ
#define BUMPER_PIN_0 PIN3
#define BUMPER_PIN_1 PIN4
#define BUMPER_PIN_2 PIN5
#define BUMPER_PIN_3 PIN6
#define BUMPER_PIN_4 PIN7

#define ALL_BUMPER_PINS (BUMPER_PIN_0 | BUMPER_PIN_1 | BUMPER_PIN_2 | BUMPER_PIN_3 | BUMPER_PIN_4)
#define NUM_BUMPERS 5

#define BUMPER_DEBOUNCE_PERIOD 1
#define DEBOUNCE_ARRAY_SIZE (BUMPER_DEBOUNCE_PERIOD + 2)
#define NEW_INDEX (DEBOUNCE_ARRAY_SIZE - 1)
#define OLD_INDEX 0


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

uint8_t read_bumpers(void);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitSimpleBumperService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunSimpleBumperService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBumperService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;
    IO_PortsSetPortInputs(BUMPER_PORT, ALL_BUMPER_PINS);
    
    ES_Timer_InitTimer(BUMPER_SERVICE_TIMER, SERVICE_TIMER_TICKS);
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostSimpleBumperService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostBumperService(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}


/**
 * @Function RunSimpleBumperService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent) {
static uint8_t states[DEBOUNCE_ARRAY_SIZE];
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/

    switch (ThisEvent.EventType) {
        case ES_INIT:
            // No hardware initialization or single time setups, those
            // go in the init function above.
            //
            // This section is used to reset service for some reason
            break;
        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break;
        case ES_TIMEOUT:
            ES_Timer_InitTimer(BUMPER_SERVICE_TIMER, SERVICE_TIMER_TICKS);

            states[NEW_INDEX] = read_bumpers();
            /* Shift your old values back for debouncing, check newer states for equality */
            uint8_t eventOccurred = 1;
            uint8_t i, j;
            for (i = OLD_INDEX, j = OLD_INDEX + 2; i < NEW_INDEX; i++, j++) {
                if (j < NEW_INDEX && eventOccurred) {
                    if (states[j] != states[j + 1]) { //tests for equality of the newest states
                        eventOccurred = 0;
                    }
                }
                states[i] = states[i + 1]; //shift values back, after checking for equality
            }
            if (states[OLD_INDEX] == states[NEW_INDEX]) {
                eventOccurred = 0;
            }

            if (eventOccurred) {
                ES_EventTyp_t currentEventType;
                //Determines the changes from old bump states to the newest one
                uint16_t releaseBumpEvents = (states[OLD_INDEX]&(states[NEW_INDEX]^states[OLD_INDEX]));
                uint16_t pressBumpEvents = (states[NEW_INDEX]&(states[NEW_INDEX]^states[OLD_INDEX]));
                if (releaseBumpEvents) {
                    currentEventType = BUMPER_RELEASED;
                } else {
                    currentEventType = BUMPER_PRESSED;
                }

                uint16_t currentEventParam = pressBumpEvents; // Set low bits
                currentEventParam |= (releaseBumpEvents << NUM_BUMPERS); // Set hi bits
                ReturnEvent.EventType = currentEventType;
                ReturnEvent.EventParam = currentEventParam;
                
                
                #ifdef BUMPER_SERVICE_TEST
                    printf("\r\nEvent: %s\tParam: 0x%X",
                        EventNames[ReturnEvent.EventType], ReturnEvent.EventParam);
                #else
                    PostSomewhere();
                #endif
            }
            break;    
        default:
            break;
    }
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

uint8_t read_bumpers(void) {
    uint8_t states = 0;
    states = IO_PortsReadPort(BUMPER_PORT) & ALL_BUMPER_PINS;
    states = states >> 3; // shift pins to be zero indexed
    
    return states;
}