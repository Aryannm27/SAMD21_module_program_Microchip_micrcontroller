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


char txdata[]="abcdefghijklmnopqrstuvwxyz\n";
char rxdata[sizeof(txdata)];
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    while ( true )
    {
        /* Maintain stat
         * e machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
//        SS_M_Clear();
        SERCOM3_SPI_Read(rxdata, sizeof(rxdata));
        SERCOM3_SPI_Write(txdata, sizeof(txdata));
        SERCOM5_USART_Write(rxdata, sizeof(rxdata));      
//        SS_M_Set(); 
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

