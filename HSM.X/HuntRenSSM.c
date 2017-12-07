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
#include "HuntRenSSM.h"

#include "FollowTapeSSM.h"
#include "AvoidObstacleSSM.h"
#include "ChargeBeaconSSM.h"

#include "Motion.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define FRUSTRATION_TICKS  3500

#define CRAWL_TICKS 1500
#define TINY_TURN_TICKS 50
#define TINY_REVERSE_TICKS 100
#define LINEUP_REVERSE_TICKS 100


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
    LineupReverse,
    TankRight,
    Lineup,
    OpenRenDoor,
    ConfirmKill,
    VictoryDance,
} HuntRenSSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"ChargeBeacon",
	"FollowTape",
	"AvoidObstacle",
	"LineupReverse",
	"TankRight",
	"Lineup",
	"OpenRenDoor",
	"ConfirmKill",
	"VictoryDance",
};


static HuntRenSSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;
static ES_Event NewEvent; // Used for passing up events



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
uint8_t InitHuntRenSSM(void) {
    ES_Event returnEvent;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    returnEvent = RunHuntRenSSM(INIT_EVENT);
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
ES_Event RunHuntRenSSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    HuntRenSSMState_t nextState;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = ChargeBeacon;
                makeTransition = TRUE;
                InitChargeBeaconSSM();
                NewEvent.EventType = MOTION_LIFT_REN;
                PostHSM(NewEvent);
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

                case BUMPER_PRESSED:
                    if (ThisEvent.EventParam & BUMPER_1_PRESSED) {
                        nextState = LineupReverse;
                    } else if (ThisEvent.EventParam & (BUMPER_0_PRESSED | BUMPER_2_PRESSED | BUMPER_3_PRESSED)) {
                        nextState = AvoidObstacle;
                        InitAvoidObstacleSSM();
                    }
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_NO_EVENT:
                default:
                    break;
            }
            break;
            
        case LineupReverse:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_move(REVERSE, 40);
                    ES_Timer_InitTimer(DRIVE_TIMER, LINEUP_REVERSE_TICKS);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == DRIVE_TIMER) {
                        nextState = TankRight;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case TankRight:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_tank_right();
                    ES_Timer_InitTimer(DRIVE_TIMER, LEFT_NINETY_DEGREE_TURN_TICKS);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == DRIVE_TIMER) {
                        nextState = Lineup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case Lineup:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_pivot_left(FORWARD, MAX_SPEED);
                    break;

                case BUMPER_PRESSED:
                    if (ThisEvent.EventParam & BUMPER_2_PRESSED ) {
                        nextState = OpenRenDoor;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
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


        case OpenRenDoor:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_open_ren_door();
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
        RunHuntRenSSM(EXIT_EVENT);
        CurrentState = nextState;
        RunHuntRenSSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/