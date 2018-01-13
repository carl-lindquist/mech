/*
 * File:   hello_world_main.c
 * Author: clindqui
 *
 * Created on October 1, 2017, 12:09 PM
 */


#include "xc.h"

#include <BOARD.h>
#include <stdio.h>
#include "IO_Ports.h"

int main(void) {
    BOARD_Init();
    printf("Hello World!");
    
    IO_PortsSetPortInputs(PORTZ, PIN4);
    int i;
    
    while (1) {
        printf("Port Z pin 4: %d\r\n", (IO_PortsReadPort(PORTZ) & PIN4) > 0);
        for (i=0; i <10000; i++);
    }
}
