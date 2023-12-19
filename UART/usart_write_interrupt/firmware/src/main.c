t/*******************************************************************************
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

char datad[]="abcdefghijklmnopqrstuvwxyz\n";
char op[sizeof(datad)];
int c=0;
void callbask(uintptr_t context){
    c++;
    GPIO_PA01_Set();
    //SYSTICK_DelayMs ( 500 );
    for(int i=0;i<100000;i++);
    GPIO_PA01_Clear();
    for(int i=0;i<100000;i++);
    SERCOM0_USART_Read(op,sizeof(op));
    SERCOM5_USART_Write(op,sizeof(op));
//    }
 }
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    SERCOM0_USART_WriteCallbackRegister( callbask,0 );
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
//        printf("ip %d\n",c);
        SERCOM0_USART_Write( datad, sizeof(datad));
//        printf("%d is\n",c);
//        SERCOM0_USART_Read(op,sizeof(op));
//        printf("is %d\n",c);
//        SERCOM5_USART_Write(op,sizeof(op));
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

