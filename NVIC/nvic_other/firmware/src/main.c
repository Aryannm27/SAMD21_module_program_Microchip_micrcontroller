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
char sendd[]="helo";
char rdata[5];
uint8_t wrdata[]="hii2c";
uint8_t rddata[5];
//static void callback(uintptr_t context){
//    GPIO_PA00_Set();
////    for(int i=0;i<100;i++);
////    GPIO_PA00_Clear();
////    for(int i=0;i<100;i++);
//}
 void call(){
//    if( I2C_ErrorGet()==I2C_ERROR_NONE )
    SERCOM2_I2C_Read(0x24,rddata, 5);
    SERCOM5_USART_Write( rddata, 5 );
}
//void callb(uintptr_t context){
////    if( SPI_ERROR_NONE == SPI3_ErrorGet())
////            {
////                GPIO_PA18_Clear();
////        SERCOM3_SPI_Read(rdata, sizeof(rdata));
////        SERCOM3_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_DRE_Msk)==SERCOM_SPIM_INTFLAG_DRE_Msk
////        GPIO_PA18_Set();
////                
////            }
//    
//}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    //NVIC_INT_Enable();
//     EIC_InterruptEnable(1);
//     EIC_CallbackRegister(1,callback, 0);
     SERCOM2_I2C_CallbackRegister( call, 0);
//     SERCOM3_SPI_CallbackRegister(callb, 0);
//    ADC_Enable();
    
//       uint16_t adcdata;
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harony modules. */
        SYS_Tasks ( );
        GPIO_PA00_Clear();
        
//        GPIO_PA18_Clear();
//        SERCOM3_SPI_Write(sendd, sizeof(sendd));
//        GPIO_PA18_Set();
        SERCOM2_I2C_Write(0x24, wrdata, sizeof(wrdata));
        SERCOM5_USART_Write(wrdata, sizeof(wrdata));
//        SERCOM2_I2C_WriteRead(0x24, wrdata, 5, rddata, 5);
        
        
        SERCOM5_USART_Write(rdata, sizeof(rdata));
    }
//    while ( true )
//    {
//        /* Maintain state machines of all polled MPLAB Harmony modules. */
//        SYS_Tasks ( );
//          GPIO_PA00_Clear();
////        for(int i=0;i<256;i++)
////        DAC_DataWrite(i);
////        ADC_ConversionStart();
////        adcdata=ADC_ConversionResultGet();
////        printf("%d\n",adcdata);
//    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

