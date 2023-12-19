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
char sdata[]="abcdefghijklmnopqrstuvwxyz\n";
char rdata[sizeof(sdata)];
int c=0;
void callb(uintptr_t context){
    c++;
    GPIO_PA02_Set();
    //SYSTICK_DelayMs ( 500 );
    for(int i=0;i<10000;i++);
    GPIO_PA02_Clear();
    for(int i=0;i<10000;i++);
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SERCOM3_SPI_CallbackRegister(&callb,0);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        printf("% d_1",c);
        SERCOM3_SPI_WriteRead (sdata,sizeof(sdata),rdata,sizeof(rdata));
        printf("% d_2",c);
        SERCOM5_USART_Write( rdata,sizeof(rdata));
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

