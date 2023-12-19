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
#include <stdio.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
void callback(RTC_TIMER32_INT_MASK intCause, uintptr_t context){
    if(intCause && RTC_TIMER32_INT_MASK_COMPARE_MATCH)
    printf("\ninterrupt is on\n");
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    RTC_Timer32Start ( );
    RTC_Timer32CounterSet ( 0 );
    RTC_Timer32CompareSet ( 256 );
    RTC_Timer32InterruptEnable(RTC_TIMER32_INT_MASK_COMPARE_MATCH);
//    RTC_Timer32CallbackRegister ( callback, 0);
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        printf("%ld count and %ld frequency %ld period\n",RTC_Timer32CounterGet(),RTC_Timer32FrequencyGet(),RTC_Timer32PeriodGet());
//        RTC_Timer32CallbackRegister ( callback, 0);
        
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

