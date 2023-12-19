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
int p=0;
int j=0;
uint8_t rxdata[10];
uint8_t txdata[]="hello_mans";
bool callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR, uintptr_t contextHandle)
{
    rxdata[p]=SERCOM2_I2C_ReadByte();
    for(int n=0;n<100;n++);
    SERCOM2_I2C_WriteByte(txdata[p]);
    if(SERCOM2_I2C_IsBusy()==0){
        p++;
    }
    if(p==10){
            SERCOM5_USART_Write( rxdata, 10);
            p=0;
        }
    bool x;
    if (SERCOM2_I2C_ErrorGet() != SERCOM_I2C_SLAVE_ERROR_ALL)
    {
      x=true;  
    }
    else
    {
      x=false;
    }
    return x;
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    SERCOM2_I2C_CallbackRegister(callback,0);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

