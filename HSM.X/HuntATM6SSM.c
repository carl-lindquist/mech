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
#include "HuntATM6SSM.h"

#include "KillATM6SSM.h"
#include "LiftControlSSM.h"
#include "FollowTapeSSM.h"
#include "AvoidObstacleSSM.h"
#include "ChargeBeaconSSM.h"

#include "Motion.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define NUM_ATM6 3

#define FRUSTRATION_TICKS  2000
#define INITIAL_FORWARD_TICKS 500
#define CHARGE_REVERSE_TICKS 500
#define CRAWL_TICKS 
#define JIG_TICKS 300


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
            ChargeBeacon,
    FollowTape,
    AvoidObstacle,
    KillATM6,
    Jig,
    Idle,
} HuntATM6SSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"ChargeBeacon",
	"FollowTape",
	"AvoidObstacle",
	"KillATM6",
	"Jig",
	"Idle",
};


static HuntATM6SSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;
static ES_Event NewEvent; // Used for passing up events

static uint8_t atm6_destroyed_count;


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
uint8_t InitHuntATM6SSM(void) {
    ES_Event returnEvent;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    returnEvent = RunHuntATM6SSM(INIT_EVENT);
    atm6_destroyed_count = 0;
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
ES_Event RunHuntATM6SSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    HuntATM6SSMState_t nextState;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                motion_raise_bridge();
                nextState = ChargeBeacon;
                InitChargeBeaconSSM();
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ChargeBeacon:
            ThisEvent = RunChargeBeaconSSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case BEACON_CHARGE_COMPLETE:
                        motion_move(FORWARD, 40);
                        InitFollowTapeSSM();
                        nextState = FollowTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case FollowTape:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            ThisEvent = RunFollowTapeSSM(ThisEvent);
            switch (ThisEvent.EventType) {

                case TRACKWIRE_ALIGNED:
                    nextState = KillATM6;
                    InitKillATM6SSM();
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case BUMPER_PRESSED:
                    nextState = AvoidObstacle;
                    makeTransition = TRUE;
                    InitAvoidObstacleSSM();
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case AvoidObstacle:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            ThisEvent = RunAvoidObstacleSSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case OBSTACLE_AVOIDED:
                    nextState = FollowTape;
                    motion_move(FORWARD, 40);
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;


        case KillATM6:
            ThisEvent = RunKillATM6SSM(ThisEvent);
            switch (ThisEvent.EventType) {

                case ATM6_DESTROYED:
                    if (++atm6_destroyed_count == NUM_ATM6) {
                        NewEvent.EventType = ALL_ATM6_DESTROYED;
                        PostHSM(NewEvent);
                    } else {
                        nextState = Jig;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case Jig:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    motion_tank_left();
                    ES_Timer_InitTimer(DRIVE_TIMER, JIG_TICKS);
                    break;

                case ES_TIMEOUT:
                    motion_tank_right();
                    break;

                case TAPE_SENSOR_UNTRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED && check_tape_states(TAPE_0)) {
                        nextState = FollowTape;
                        InitFollowTapeSSM();
                        motion_move(FORWARD, 35);
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;



        default: // all unhandled states fall into here
            break;
    } // end switch on Current State
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunHuntATM6SSM(EXIT_EVENT);
        CurrentState = nextState;
        RunHuntATM6SSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/