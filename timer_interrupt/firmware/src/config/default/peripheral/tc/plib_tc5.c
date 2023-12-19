/*******************************************************************************
  Timer/Counter(TC5) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_TC5.c

  Summary
    TC5 PLIB Implementation File.

  Description
    This file defines the interface to the TC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "plib_tc5.h"
#include "interrupts.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: TC5 Implementation
// *****************************************************************************
// *****************************************************************************

void TC5_CaptureInitialize( void )
{
    /* Reset TC */
    TC5_REGS->COUNT16.TC_CTRLA = TC_CTRLA_SWRST_Msk;

    while((TC5_REGS->COUNT16.TC_STATUS & TC_STATUS_SYNCBUSY_Msk)!= 0U)
    {
        /* Wait for Write Synchronization */
    }

    /* Configure counter mode, prescaler, standby */
    TC5_REGS->COUNT16.TC_CTRLA = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV1 ;

    TC5_REGS->COUNT16.TC_CTRLC = TC_CTRLC_CPTEN0_Msk | TC_CTRLC_CPTEN1_Msk;

    TC5_REGS->COUNT16.TC_EVCTRL = TC_EVCTRL_EVACT_PPW | TC_EVCTRL_TCEI_Msk;

    /* Clear all interrupt flags */
    TC5_REGS->COUNT16.TC_INTFLAG = TC_INTFLAG_Msk;

}


void TC5_CaptureStart( void )
{
    /* Enable TC */
    TC5_REGS->COUNT16.TC_CTRLA |= TC_CTRLA_ENABLE_Msk;

    while((TC5_REGS->COUNT16.TC_STATUS & TC_STATUS_SYNCBUSY_Msk)!= 0U)
    {
        /* Wait for Write Synchronization */
    }
}

void TC5_CaptureStop( void )
{
    /* Disable TC */
    TC5_REGS->COUNT16.TC_CTRLA =((TC5_REGS->COUNT16.TC_CTRLA) & (uint16_t)(~TC_CTRLA_ENABLE_Msk));

    while((TC5_REGS->COUNT16.TC_STATUS & TC_STATUS_SYNCBUSY_Msk)!= 0U)
    {
        /* Wait for Write Synchronization */
    }
}

uint32_t TC5_CaptureFrequencyGet( void )
{
    return (uint32_t)(48000000UL);
}

void TC5_CaptureCommandSet(TC_COMMAND command)
{
    TC5_REGS->COUNT16.TC_CTRLBSET =(uint8_t)command << TC_CTRLBSET_CMD_Pos;
    while((TC5_REGS->COUNT16.TC_STATUS & TC_STATUS_SYNCBUSY_Msk)!= 0U)
    {
        /* Wait for Write Synchronization */
    }   
}


uint16_t TC5_Capture16bitChannel0Get( void )
{
    /* Write command to force CC register read synchronization */
    TC5_REGS->COUNT16.TC_READREQ = TC_READREQ_RREQ_Msk | (uint16_t)TC_COUNT16_CC_REG_OFST;

    while((TC5_REGS->COUNT16.TC_STATUS & TC_STATUS_SYNCBUSY_Msk)!= 0U)
    {
        /* Wait for Write Synchronization */
    }
    return (uint16_t)TC5_REGS->COUNT16.TC_CC[0];
}

uint16_t TC5_Capture16bitChannel1Get( void )
{
    /* Write command to force CC register read synchronization */
    TC5_REGS->COUNT16.TC_READREQ = TC_READREQ_RREQ_Msk | (uint16_t)TC_COUNT16_CC_REG_OFST;

    while((TC5_REGS->COUNT16.TC_STATUS & TC_STATUS_SYNCBUSY_Msk)!= 0U)
    {
        /* Wait for Write Synchronization */
    }
    return (uint16_t)TC5_REGS->COUNT16.TC_CC[1];
}


TC_CAPTURE_STATUS TC5_CaptureStatusGet(void)
{
    TC_CAPTURE_STATUS capture_status;
    capture_status = (TC_CAPTURE_STATUS) ((TC5_REGS->COUNT16.TC_INTFLAG) & TC_CAPTURE_STATUS_MSK);
    TC5_REGS->COUNT16.TC_INTFLAG = capture_status;
    return capture_status;
}
