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
uint8_t sdata[]="abcdefghijklmnopqrstuvwxyz\n";
uint8_t rdata[sizeof(sdata)];
int c=0;
void callb(){
    c++;
    GPIO_PA02_Set();
    //SYSTICK_DelayMs ( 500 );
    for(int i=0;i<100000;i++);
    GPIO_PA02_Clear();
    for(int i=0;i<100000;i++);
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SERCOM2_I2C_CallbackRegister(callb, 0);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
       SYS_Tasks ( );
       SERCOM2_I2C_WriteRead(0x24, sdata,sizeof(sdata), rdata,sizeof(rdata));
       SERCOM5_USART_Write(rdata, sizeof(rdata));
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

