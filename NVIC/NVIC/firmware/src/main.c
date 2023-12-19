/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

uint8_t rddata[5];

void calback(uintptr_t context){
    GPIO_PA02_Toggle();
}
void callback(TC_TIMER_STATUS status, uintptr_t context ){
    GPIO_PA00_Toggle();
}
void callb(){
    GPIO_PA03_Toggle();
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TC4_TimerStart(  );
    TC4_TimerCallbackRegister(callback, 0 );
    EIC_InterruptEnable(1);
    EIC_CallbackRegister(1,calback, 0);
    SERCOM2_I2C_CallbackRegister(callb, 0);
    while ( true )    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        SERCOM2_I2C_Read(0x24,rddata, sizeof(rddata));
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

