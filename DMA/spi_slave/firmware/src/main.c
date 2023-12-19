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
char send[]="abcdefghijklmnopqrstuvwxyz\n";
char receive[sizeof(send)];
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        DMAC_ChannelTransfer (DMAC_CHANNEL_0, (const void *)&SERCOM1_REGS->SPIM.SERCOM_DATA, (const void *)receive, sizeof(receive));
        DMAC_ChannelTransfer (DMAC_CHANNEL_1 ,send,(const void *)&SERCOM1_REGS->SPIM.SERCOM_DATA , sizeof(send));
        
//        SERCOM5_USART_WriteByte(receive);
        SERCOM5_USART_Write( receive,sizeof(receive) );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

