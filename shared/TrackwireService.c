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
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include <stdio.h>

#include "TrackwireService.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define SERVICE_TIMER_TICKS 20

#define DEBOUNCE_PERIOD 2
#define DEBOUNCE_ARRAY_SIZE (DEBOUNCE_PERIOD + 2)
#define NEW_INDEX (DEBOUNCE_ARRAY_SIZE - 1)
#define OLD_INDEX 0

#define TRACKWIRE_PIN AD_PORTW3

#define TRACKWIRE_ALIGNED_HI_THRESH 300
#define TRACKWIRE_ALIGNED_LO_THRESH (TRACKWIRE_ALIGNED_HI_THRESH - 100)
#define TRACKWIRE_FOUND_HI_THRESH 120
#define TRACKWIRE_FOUND_LO_THRESH (TRACKWIRE_FOUND_HI_THRESH - 30)


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

uint16_t read_trackwire_sensor(void);

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;
static uint8_t old_event_types[DEBOUNCE_ARRAY_SIZE];

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
uint8_t InitTrackwireService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;

    AD_AddPins(TRACKWIRE_PIN);

//    old_event_type = TRACKWIRE_LOST;
    ES_Timer_InitTimer(TRACKWIRE_SERVICE_TIMER, SERVICE_TIMER_TICKS);
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
uint8_t PostTrackwireService(ES_Event ThisEvent) {
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
ES_Event RunTrackwireService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    static ES_EventTyp_t old_event_type;
    
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
            ES_Timer_InitTimer(TRACKWIRE_SERVICE_TIMER, SERVICE_TIMER_TICKS);

            uint16_t new_trackwire_state = read_trackwire_sensor();
            ES_EventTyp_t new_trackwire_event_type;
            if (new_trackwire_state > TRACKWIRE_ALIGNED_HI_THRESH) {
                new_trackwire_event_type = TRACKWIRE_ALIGNED;
            } else if (new_trackwire_state > TRACKWIRE_FOUND_HI_THRESH && new_trackwire_state < TRACKWIRE_ALIGNED_LO_THRESH) {
                new_trackwire_event_type = TRACKWIRE_FOUND;
            } else if (new_trackwire_state < TRACKWIRE_FOUND_LO_THRESH)  {
                new_trackwire_event_type = TRACKWIRE_LOST;
            } else {
                new_trackwire_event_type = old_event_type;
            }
            
            if (new_trackwire_event_type != old_event_type) {
                ReturnEvent.EventType = new_trackwire_event_type;
                ReturnEvent.EventParam = new_trackwire_state;
                old_event_type = new_trackwire_event_type;
            
            

#ifdef TRACKWIRE_SERVICE_TEST
                printf("\r\nEvent: %s\tParam: 0x%X",
                        EventNames[ReturnEvent.EventType], ReturnEvent.EventParam);
#else
                //                    PostTapeSensorService(ReturnEvent);
                //                    ES_PostList00(ReturnEvent);
                PostFollowFSM(ReturnEvent);
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


uint16_t read_trackwire_sensor(void) {
    return AD_ReadADPin(TRACKWIRE_PIN);
}