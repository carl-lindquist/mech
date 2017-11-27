/* 
 * File:   UserEventCheckers.h
 * Author: Gabriel Hugh Elkaim
 *
 * This EventCheckers file will work with simple services, FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on September 27, 2013, 8:37 AM
 * Modified on September 12, 2016, 7:59 PM
 */

#ifndef USER_EVENT_CHECKERS_H
#define	USER_EVENT_CHECKERS_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "BOARD.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

 

/**
 * @Function CheckBumpers(void)
 * @param none
 * @return TRUE or FALSE
 * @brief   This function is a simple event checker which can post to a service
 *          but currently does not. It responds to a change in the bumpers by
 *          posting an event to the GenericService with a param which indicates
 *          which bumpers were pressed. No debouncing and is prone to spamming.
 * @note Pretty good template.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Conrad Esch*/
uint8_t CheckBumpers(void);


#endif	/* USER_EVENT_CHECKERS_H */

