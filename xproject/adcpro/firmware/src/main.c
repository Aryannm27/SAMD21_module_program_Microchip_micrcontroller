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
uint16_t adc_result=0;
float voltage;
void ADC(ADC_POSINPUT channel){
    ADC_ChannelSelect( ADC_POSINPUT_PIN0, ADC_NEGINPUT_GND );
    ADC_ConversionStart( );
    adc_result = ADC_ConversionResultGet(  );
    voltage = adc_result * 3.3 / 4096;
    printf("vol = %.3f ", voltage);
}
int adc_var1=0;
int adc_var2=0;
void timer_loop(TC_TIMER_STATUS status, uintptr_t context){
    adc_var1=1;
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TC3_TimerStart();
    TC3_TimerCallbackRegister( timer_loop, 0 );
    ADC_Enable(  );
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
//        if(adc_var1==1){
            ADC();
//        }
        adc_var1=0;
//        printf("\n");
    }
    

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

