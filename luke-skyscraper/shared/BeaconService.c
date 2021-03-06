/*
 * File: TrackwireService.c
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
#include "ES_Configure.h"
#include "ES_Framework.h"
#include <stdio.h>
#include "IO_Ports.h"

#include "BeaconService.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define SERVICE_TIMER_TICKS 20

#define BEACON_PORT PORTX
#define BEACON_PIN PIN8


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

uint8_t read_beacon_sensor(void);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;
static uint8_t old_event_type;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTrackwireService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunSimpleBumperService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBeaconService(uint8_t Priority) {
    ES_Event ThisEvent;
    MyPriority = Priority;

    IO_PortsSetPortInputs(BEACON_PORT, BEACON_PIN);

    old_event_type = BEACON_LOST;
    ES_Timer_InitTimer(BEACON_SERVICE_TIMER, SERVICE_TIMER_TICKS);
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTrackwireService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostBeaconService(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}


/**
 * @Function RunTrackwireService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBeaconService(ES_Event ThisEvent) {
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
            ES_Timer_InitTimer(BEACON_SERVICE_TIMER, SERVICE_TIMER_TICKS);

            uint8_t new_beacon_state = read_beacon_sensor();
            ES_EventTyp_t new_event_type = (new_beacon_state == 1 ? BEACON_FOUND : BEACON_LOST);   
            
            if (new_event_type != old_event_type) {
                ReturnEvent.EventType = new_event_type;
                ReturnEvent.EventParam =0x00;
                old_event_type = new_event_type;
            
            

#ifdef BEACON_SERVICE_TEST
                printf("\r\nEvent: %s\tParam: 0x%X",
                        EventNames[ReturnEvent.EventType], ReturnEvent.EventParam);
#else
                ES_PostList00(ReturnEvent);
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


uint8_t read_beacon_sensor(void) {
    return ((IO_PortsReadPort(BEACON_PORT) & BEACON_PIN) != 0);
}