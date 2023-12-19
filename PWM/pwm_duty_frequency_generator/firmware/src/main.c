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

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYS_Initialize ( NULL );
    TCC0_PWMStart();
    SYSTICK_TimerStart ( );
    SYSTICK_TimerPeriodSet (100000);
    int i,j,k;
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        TCC0_PWM24bitPeriodSet(1000);        
        TCC0_PWM24bitDutySet(TCC0_CHANNEL0, 500);
        printf("enter yes(1) or No(0) for change");
        scanf("%d",&k);
        if(k==1){
            printf("enter the value of frequency:");
            scanf("%d",&i);
            printf("enter the value of duty cycle:");
            scanf("%d",&j);
            TCC0_PWM24bitPeriodSet(i);        
            TCC0_PWM24bitDutySet(TCC0_CHANNEL0, j);
        }
        
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

