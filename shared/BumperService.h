/*
 * File: SimpleBumperService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

#ifndef BUMPER_SERVICE_H  
#define BUMPER_SERVICE_H


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define BUMPER_0 0x01 
#define BUMPER_1 0x02
#define BUMPER_2 0x04
#define BUMPER_3 0x08
#define BUMPER_4 0x10

#define BUMPER_0_PRESSED 0x0001
#define BUMPER_1_PRESSED 0x0002
#define BUMPER_2_PRESSED 0x0004
#define BUMPER_3_PRESSED 0x0008
#define BUMPER_4_PRESSED 0x0010

#define BUMPER_0_RELEASED 0x0020
#define BUMPER_1_RELEASED 0x0040
#define BUMPER_2_RELEASED 0x0080
#define BUMPER_3_RELEASED 0x0100
#define BUMPER_4_RELEASED 0x0200

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

uint8_t check_bumper_states(uint8_t sensor_pattern);
 
/**
 * @Function InitBumperService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief 
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBumperService(uint8_t Priority);

/**
 * @Function PostBumperService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief 
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostBumperService(ES_Event ThisEvent);

/**
 * @Function RunBumperService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent);



#endif /* BUMPER_SERVICE_H */

