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
uint8_t RX;
uint8_t TX='Y';
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart (  );
    SYSTICK_TimerPeriodSet ( 100000 );
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        DMAC_ChannelTransfer (DMAC_CHANNEL_0, (const void*)&SERCOM0_REGS->USART_INT.SERCOM_DATA, &RX, sizeof(RX));
        SERCOM5_USART_Write( &RX, sizeof(RX) );
        DMAC_ChannelTransfer (DMAC_CHANNEL_1, &TX, (const void*)&SERCOM0_REGS->USART_INT.SERCOM_DATA, sizeof(TX));
        
        SYSTICK_DelayMs ( 100 );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/
