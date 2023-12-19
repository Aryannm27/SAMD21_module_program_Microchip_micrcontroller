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
char sdata[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
char rdata[sizeof(sdata)];
int c=0;
void caback(uintptr_t context){
//    if( SERCOM3_SPI_ErrorGet() == SPI_SLAVE_ERROR_NONE )
//            {
//                
//            }
                c++;
                GPIO_PA02_Set();
                //SYSTICK_DelayMs ( 500 );
                for(int i=0;i<100000;i++);
                GPIO_PA02_Clear();
                for(int i=0;i<100000;i++);
   
//    SERCOM1_SPI_Read(rdata, sizeof(rdata));
//    SERCOM5_USART_Read( rdata,sizeof(rdata) );
    
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SERCOM3_SPI_CallbackRegister(&caback,0);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
//        SS_Clear();
        
//      for(int i=0;i<1000;i++);
        printf("%d1",c);
        SERCOM3_SPI_Read(rdata, sizeof(rdata));
        printf("%d2",c);
        SERCOM3_SPI_Write(sdata,sizeof(sdata));
        printf("%d3",c);
        SERCOM5_USART_Write( rdata,sizeof(rdata));
//        SS_Set();
        
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

