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
uint8_t x;
bool callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle){
    
    if(event!=SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR){
       x=SERCOM1_I2C_ReadByte();
       printf("%c",x);
//        SERCOM5_USART_Write( &x, sizeof(x) );
       return true;
    }
    return false;
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SERCOM1_I2C_CallbackRegister(callback, 0);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

