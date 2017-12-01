/*
 * File: TemplateFSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Flat State Machine to work with the Events and Services
 * Frameword (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 *Generally you will just be modifying the statenames and the run function
 *However make sure you do a find and replace to convert every instance of
 *  "Template" to your current state machine's name
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"

#include "FollowFSM.h"
#include <BOARD.h>
#include <stdio.h>

#include "TapeSensorService.h"
#include "Motion.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define FRUSTRATION_TICKS  5000

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine.*/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/

/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

typedef enum {
    InitPState,
    FindTape,
    Align,
            CornerReverse,
    AdjustLeft,
    AdjustRight,
} FollowFSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"FindTape",
	"Align",
	"CornerReverse",
	"AdjustLeft",
	"AdjustRight",
};


static FollowFSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateFSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitFollowFSM(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateFSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostFollowFSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateFSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the flat state machine,
 *        as this is called any time a new event is passed to the event queue. This
 *        function will be called recursively to implement the correct order for a
 *        state transition to be: exit current state -> enter next state using the
 *        ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed."
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunFollowFSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    FollowFSMState_t nextState; // <- need to change enum type here

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = FindTape;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case FindTape: // in the first state, replace this with appropriate state
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_move(FORWARD, MIN_SPEED);
                    break;
                case TAPE_SENSOR_TRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_TRIPPED) {
                        nextState = Align;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;
            
        case CornerReverse: // in the first state, replace this with appropriate state
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_move(REVERSE, MIN_SPEED);
                    break;
                case TAPE_SENSOR_UNTRIPPED:
                    if (ThisEvent.EventParam & TAPE_2_UNTRIPPED) {
                        nextState = Align;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;


        case AdjustRight: // in the first state, replace this with appropriate state
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    ES_Timer_InitTimer(TAPE_TURN_TIMER, TAPE_ADJUST_TICKS);
                    motion_pivot_right(FORWARD);
                    break;
                case TAPE_SENSOR_UNTRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED) {
                        nextState = AdjustLeft;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    
                case TAPE_SENSOR_TRIPPED:
                    if (ThisEvent.EventParam & TAPE_2_TRIPPED) {
                        nextState = CornerReverse;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case AdjustLeft: // in the first state, replace this with appropriate state
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    ES_Timer_InitTimer(TAPE_TURN_TIMER, TAPE_ADJUST_TICKS);
                    motion_pivot_left(FORWARD);
                    break;
                case TAPE_SENSOR_TRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_TRIPPED) {
                        nextState = AdjustRight;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam & TAPE_2_TRIPPED) {
                        nextState = CornerReverse;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case Align: // in the first state, replace this with appropriate state
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(FRUSTRATION_TIMER, FRUSTRATION_TICKS);
                    motion_tank_right();
                    break;
                case TAPE_SENSOR_UNTRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED) {  // && ~(get_tape_states() & TAPE_2)) {
                        nextState = AdjustLeft;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == FRUSTRATION_TIMER)
                    nextState = FindTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;


        default: // all unhandled states fall into here
            break;
    } // end switch on Current State
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFollowFSM(EXIT_EVENT);
        CurrentState = nextState;
        RunFollowFSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/