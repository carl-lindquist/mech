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

#ifndef TapeSensorService_H  
#define TapeSensorService_H


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define TAPE_0_TRIPPED 0x0001
#define TAPE_1_TRIPPED 0x0002
#define TAPE_2_TRIPPED 0x0004
#define TAPE_3_TRIPPED 0x0008
#define TAPE_4_TRIPPED 0x0010

#define TAPE_0_UNTRIPPED 0x0020
#define TAPE_1_UNTRIPPED 0x0040
#define TAPE_2_UNTRIPPED 0x0080
#define TAPE_3_UNTRIPPED 0x0100
#define TAPE_4_UNTRIPPED 0x0200

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Reads the most recent value of the tape sensor states. This does not read the
 * AD Pins directly, and will only return the value last recorded by the tape
 * sensor service. Non-blocking.
 * @return The state of the tape sensors as a uint8_t
 */
uint8_t get_tape_states(void);
 
/**
 * @Function InitTapeService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief 
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTapeSensorService(uint8_t Priority);

/**
 * @Function PostTapeService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief 
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTapeSensorService(ES_Event ThisEvent);

/**
 * @Function RunTapeService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunTapeSensorService(ES_Event ThisEvent);



#endif /* TapeSensorService_H */

