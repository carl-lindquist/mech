/*
 * File: AvoidObstacleSSM.c
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
#include "AvoidObstacleSSM.h"

#include "Motion.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define FRUSTRATION_TICKS  3000

#define IGNORE_TAPE_TICKS 1000
#define PIVOT_TICKS 400
#define REVERSE_TICKS 500

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
    Reverse,
    Tank,
    IgnoreTapeBank,
    PivotAway,
    Bank,
    LookForTape,
    ConfirmBorderTape,
    Align,
} AvoidObstacleState_t;

static const char *StateNames[] = {
	"InitPState",
	"Reverse",
	"Tank",
	"IgnoreTapeBank",
	"PivotAway",
	"Bank",
	"LookForTape",
	"ConfirmBorderTape",
	"Align",
};


static AvoidObstacleState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;
static ES_Event NewEvent; // Used for passing up events

static uint16_t parallel_ticks;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitAvoidObstacleSSM(void)
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitAvoidObstacleSSM(void) {
    ES_Event returnEvent;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    returnEvent = RunAvoidObstacleSSM(INIT_EVENT);
    // post the initial transition event
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function RunAvoidObstacleSSM(ES_Event ThisEvent)
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
ES_Event RunAvoidObstacleSSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    AvoidObstacleState_t nextState;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                motion_stop();

                // now put the machine into the actual initial state

                nextState = Reverse;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Reverse:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_move(REVERSE, 50);
                    ES_Timer_InitTimer(DRIVE_TIMER, REVERSE_TICKS);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == DRIVE_TIMER) {
                        nextState = Tank;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case TAPE_SENSOR_TRIPPED:
                    if (ThisEvent.EventParam & TAPE_2_TRIPPED) {
                        motion_stop();
                        nextState = Tank;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Tank:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_tank_right();
                    ES_Timer_InitTimer(DRIVE_TIMER, RIGHT_NINETY_DEGREE_TURN_TICKS);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == DRIVE_TIMER) {
                        nextState = IgnoreTapeBank;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;



        case IgnoreTapeBank:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_bank_left(FORWARD);
                    ES_Timer_InitTimer(DRIVE_TIMER, IGNORE_TAPE_TICKS);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == DRIVE_TIMER) {
                        nextState = Bank;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    
                case BUMPER_PRESSED:
                    nextState = PivotAway;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Bank:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_bank_left(FORWARD);
                    break;

                case TAPE_SENSOR_UNTRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED) {
                        nextState = Align;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case BUMPER_PRESSED:
                    nextState = PivotAway;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            
        case PivotAway:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    motion_pivot_left(REVERSE, 60);
                    ES_Timer_InitTimer(DRIVE_TIMER, PIVOT_TICKS);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == DRIVE_TIMER) {
                        nextState = Bank;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case Align:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(FRUSTRATION_TIMER, FRUSTRATION_TICKS);
                    motion_tank_right();
                    break;

                case TAPE_SENSOR_UNTRIPPED:
                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED) {
                        motion_stop();
                        NewEvent.EventType = OBSTACLE_AVOIDED;
                        PostHSM(NewEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == FRUSTRATION_TIMER) {
                        
                        NewEvent.EventType = OBSTACLE_AVOIDED;
                        PostHSM(NewEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

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
        RunAvoidObstacleSSM(EXIT_EVENT);
        CurrentState = nextState;
        RunAvoidObstacleSSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/






///*
// * File: AvoidObstacleSSM.c
// * Author: J. Edward Carryer
// * Modified: Gabriel H Elkaim
// *
// * Template file to set up a Flat State Machine to work with the Events and Services
// * Frameword (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
// * will need to be modified to fit your exact needs, and most of the names will have
// * to be changed to match your code.
// *
// * This is provided as an example and a good place to start.
// *
// *Generally you will just be modifying the statenames and the run function
// *However make sure you do a find and replace to convert every instance of
// *  "Template" to your current state machine's name
// * History
// * When           Who     What/Why
// * -------------- ---     --------
// * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
// * 01/15/12 11:12 jec      revisions for Gen2 framework
// * 11/07/11 11:26 jec      made the queue static
// * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
// * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
// */
//
//
///*******************************************************************************
// * MODULE #INCLUDE                                                             *
// ******************************************************************************/
//#include "ES_Configure.h"
//#include "ES_Framework.h"
//#include "AvoidObstacleSSM.h"
//
//
//#include <BOARD.h>
//#include <stdio.h>
//
//#include "HSM.h"
//
//
//#include "Motion.h"
//
//
///*******************************************************************************
// * MODULE #DEFINES                                                             *
// ******************************************************************************/
//
//#define FRUSTRATION_TICKS  2000
//
//#define REVERSE_TICKS 600
//#define UNEXPECTED_BUMP_REVERSE_TICKS 100
//#define AWAY_TICKS 950
//#define DEFAULT_PARALLEL_TICKS (1900)
//#define REDUCED_PARALLEL_TICKS (2050)
//#define TOWARD_TICKS (AWAY_TICKS - 350)
//
//#define PIVOT_AWAY_TICKS 200
//
//
///*******************************************************************************
// * PRIVATE FUNCTION PROTOTYPES                                                 *
// ******************************************************************************/
///* Prototypes for private functions for this machine. They should be functions
//   relevant to the behavior of this state machine.*/
//
//
///*******************************************************************************
// * PRIVATE MODULE VARIABLES                                                            *
// ******************************************************************************/
//
///* You will need MyPriority and the state variable; you may need others as well.
// * The type of state variable should match that of enum in header file. */
//
//typedef enum {
//    InitPState,
//    Reverse,
//    FirstTank,
//    Away,
//    BumpReverse,
//    SecondTank,
//    Parallel,
//    ThirdTank,
//    Toward,
//    PivotAway,
//    BankLeft,
//    Crawl,
//    Align,
//} AvoidObstacleState_t;
//
//static const char *StateNames[] = {
//	"InitPState",
//	"Reverse",
//	"FirstTank",
//	"Away",
//	"BumpReverse",
//	"SecondTank",
//	"Parallel",
//	"ThirdTank",
//	"Toward",
//	"PivotAway",
//	"BankLeft",
//	"Crawl",
//	"Align",
//};
//
//
//static AvoidObstacleState_t CurrentState = InitPState; // <- change enum name to match ENUM
//static uint8_t MyPriority;
//static ES_Event NewEvent; // Used for passing up events
//
//static uint16_t parallel_ticks;
//
//
///*******************************************************************************
// * PUBLIC FUNCTIONS                                                            *
// ******************************************************************************/
//
///**
// * @Function InitAvoidObstacleSSM(void)
// * @return TRUE or FALSE
// * @brief This will get called by the framework at the beginning of the code
// *        execution. It will post an ES_INIT event to the appropriate event
// *        queue, which will be handled inside RunTemplateFSM function. Remember
// *        to rename this to something appropriate.
// *        Returns TRUE if successful, FALSE otherwise
// * @author J. Edward Carryer, 2011.10.23 19:25 */
//uint8_t InitAvoidObstacleSSM(void) {
//    ES_Event returnEvent;
//    // put us into the Initial PseudoState
//    CurrentState = InitPState;
//    returnEvent = RunAvoidObstacleSSM(INIT_EVENT);
//    // post the initial transition event
//    if (returnEvent.EventType == ES_NO_EVENT) {
//        return TRUE;
//    } else {
//        return FALSE;
//    }
//}
//
///**
// * @Function RunAvoidObstacleSSM(ES_Event ThisEvent)
// * @param ThisEvent - the event (type and param) to be responded.
// * @return Event - return event (type and param), in general should be ES_NO_EVENT
// * @brief This function is where you implement the whole of the flat state machine,
// *        as this is called any time a new event is passed to the event queue. This
// *        function will be called recursively to implement the correct order for a
// *        state transition to be: exit current state -> enter next state using the
// *        ES_EXIT and ES_ENTRY events.
// * @note Remember to rename to something appropriate.
// *       Returns ES_NO_EVENT if the event have been "consumed."
// * @author J. Edward Carryer, 2011.10.23 19:25 */
//ES_Event RunAvoidObstacleSSM(ES_Event ThisEvent) {
//    uint8_t makeTransition = FALSE; // use to flag transition
//    AvoidObstacleState_t nextState;
//
//    ES_Tattle(); // trace call stack
//
//    switch (CurrentState) {
//        case InitPState: // If current state is initial Psedudo State
//            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
//            {
//                // this is where you would put any actions associated with the
//                // transition from the initial pseudo-state into the actual
//                // initial state
//                motion_stop();
//
//                // now put the machine into the actual initial state
//
//                nextState = Reverse;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//            break;
//
//        case Reverse:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_move(REVERSE, 70);
//                    ES_Timer_InitTimer(DRIVE_TIMER, REVERSE_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = FirstTank;
//                        parallel_ticks = DEFAULT_PARALLEL_TICKS;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case TAPE_SENSOR_TRIPPED:
//                    if (ThisEvent.EventParam & TAPE_2_TRIPPED) {
//                        nextState = FirstTank;
//                        parallel_ticks = REDUCED_PARALLEL_TICKS;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case FirstTank:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_tank_right();
//                    ES_Timer_InitTimer(DRIVE_TIMER, RIGHT_NINETY_DEGREE_TURN_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = Away;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case Away:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_move(FORWARD, MAX_SPEED);
//                    ES_Timer_InitTimer(DRIVE_TIMER, AWAY_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = SecondTank;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case BUMPER_PRESSED:
//                    nextState = BumpReverse;
//                    makeTransition = TRUE;
//                    ThisEvent.EventType = ES_NO_EVENT;
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//
//            }
//            break;
//
//        case BumpReverse:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_move(REVERSE, MIN_SPEED);
//                    ES_Timer_InitTimer(DRIVE_TIMER, UNEXPECTED_BUMP_REVERSE_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = SecondTank;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case SecondTank:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_tank_left();
//                    ES_Timer_InitTimer(DRIVE_TIMER, LEFT_NINETY_DEGREE_TURN_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = Parallel;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case Parallel:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_move(FORWARD, 60);
//                    ES_Timer_InitTimer(DRIVE_TIMER, parallel_ticks);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = ThirdTank;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case TAPE_SENSOR_TRIPPED:
//                    if (check_tape_states(TAPE_0) && check_tape_states(TAPE_2) && !check_tape_states(TAPE_1)) {
//                        motion_stop(); // no time to waste here
//                        nextState = Align;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case BUMPER_PRESSED:
//                    nextState = PivotAway;
//                    makeTransition = TRUE;
//                    ThisEvent.EventType = ES_NO_EVENT;
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//            
//        case PivotAway:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_pivot_left(REVERSE, 40);
//                    ES_Timer_InitTimer(DRIVE_TIMER, PIVOT_AWAY_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = BankLeft;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//            
//        case BankLeft:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_bank_left(FORWARD);
//                    break;
//
//                case TAPE_SENSOR_TRIPPED:
//                    if (check_tape_states(TAPE_0) && check_tape_states(TAPE_2)) {
//                        nextState = Align;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//            
//
//        case ThirdTank:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_tank_left();
//                    ES_Timer_InitTimer(DRIVE_TIMER, LEFT_NINETY_DEGREE_TURN_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = Toward;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case Toward:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_move(FORWARD, MAX_SPEED);
//                    ES_Timer_InitTimer(DRIVE_TIMER, TOWARD_TICKS);
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == DRIVE_TIMER) {
//                        nextState = Crawl;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case Crawl:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    motion_move(FORWARD, 40);
//                    break;
//
//                case TAPE_SENSOR_UNTRIPPED:
//                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED) {
//                        nextState = Align;
//                        makeTransition = TRUE;
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        case Align:
//            switch (ThisEvent.EventType) {
//                case ES_ENTRY:
//                    ES_Timer_InitTimer(FRUSTRATION_TIMER, FRUSTRATION_TICKS);
//                    motion_tank_right();
//                    break;
//
//                case TAPE_SENSOR_UNTRIPPED:
//                    if (ThisEvent.EventParam & TAPE_1_UNTRIPPED) {
//                        motion_stop();
//                        NewEvent.EventType = OBSTACLE_AVOIDED;
//                        PostHSM(NewEvent);
//                        ThisEvent.EventType = ES_NO_EVENT;
//                    }
//                    break;
//
//                case ES_TIMEOUT:
//                    if (ThisEvent.EventParam == FRUSTRATION_TIMER) {
//                        NewEvent.EventType = OBSTACLE_AVOIDED;
//                        PostHSM(NewEvent);
//                        ThisEvent.EventType = ES_NO_EVENT;
//                        motion_move(FORWARD, 50);
//                    }
//                    break;
//
//                case ES_NO_EVENT:
//                default: // all unhandled events pass the event back up to the next level
//                    break;
//            }
//            break;
//
//        default: // all unhandled states fall into here
//            break;
//    } // end switch on Current State
//    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
//        // recursively call the current state with an exit event
//        RunAvoidObstacleSSM(EXIT_EVENT);
//        CurrentState = nextState;
//        RunAvoidObstacleSSM(ENTRY_EVENT);
//    }
//    ES_Tail(); // trace call stack end
//    return ThisEvent;
//}
//
//
///*******************************************************************************
// * PRIVATE FUNCTIONS                                                           *
// ******************************************************************************/