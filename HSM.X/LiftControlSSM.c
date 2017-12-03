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
#include <BOARD.h>
#include <stdio.h>

#include "HSM.h"
#include "LiftControlSSM.h"

#include "BumperService.h"
#include "Motion.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define INIT_TICKS 100
#define DOWN_TO_UP_TICKS 2000


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine.*/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/

static ES_Event NewEvent;

/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

typedef enum {
    InitPState,
    Down,
    Up,
    FindOrigin,
    MoveToRen,
} LiftControlSSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"Down",
	"Up",
	"FindOrigin",
	"MoveToRen",
};


static LiftControlSSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitFollowTapeSSM(void)
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitLiftControlSSM(void) {
    ES_Event returnEvent;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    returnEvent = RunLiftControlSSM(INIT_EVENT);
    // post the initial transition event
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function RunFollowTapeSSM(ES_Event ThisEvent)
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
ES_Event RunLiftControlSSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    LiftControlSSMState_t nextState;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                ES_Timer_InitTimer(FRUSTRATION_TIMER, INIT_TICKS);
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                if (ThisEvent.EventParam == FRUSTRATION_TIMER) {
                    // now put the machine into the actual initial state
                    if (check_bumper_states(BUMPER_4)) {
                        nextState = Down;
                        NewEvent.EventType = MOTION_LIFT_COMPLETE;
                        PostHSM(NewEvent);
                    } else {
                        nextState = FindOrigin;
                    }
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
            }
            break;


        case FindOrigin:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_lower_lift();
                    break;
                case BUMPER_PRESSED:
                    if (ThisEvent.EventParam & BUMPER_4_PRESSED) {
                        
                        NewEvent.EventType = MOTION_LIFT_COMPLETE;
                        PostHSM(NewEvent);
                        nextState = Down;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case MoveToRen:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(LIFT_TIMER, DOWN_TO_UP_TICKS);
                    motion_raise_lift();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == LIFT_TIMER) {
                        NewEvent.EventType = MOTION_LIFT_COMPLETE;
                        PostHSM(NewEvent);
                        nextState = Up;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Down:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_stop_lift();
                    break;

                case MOTION_LIFT_UP:
                    nextState = MoveToRen;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Up:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_stop_lift();
                    NewEvent.EventType = MOTION_LIFT_COMPLETE;
                    PostHSM(NewEvent);
                    break;

                case MOTION_LIFT_DOWN:
                    nextState = FindOrigin;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunLiftControlSSM(EXIT_EVENT);
        CurrentState = nextState;
        RunLiftControlSSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/