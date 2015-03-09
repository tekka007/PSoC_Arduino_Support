/*  --------------------------------------------------------------------------
* Copyright 2013, Cypress Semiconductor Corporation.
*
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international
* treaty provisions. Cypress hereby grants to licensee a personal,
* non-exclusive, non-transferable license to copy, use, modify, create
* derivative works of, and compile the Cypress Source Code and derivative
* works for the sole purpose of creating custom software in support of
* licensee product to be used only in conjunction with a Cypress integrated
* circuit as specified in the applicable agreement. Any reproduction,
* modification, translation, compilation, or representation of this
* software except as specified above is prohibited without the express
* written permission of Cypress.
* 
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND,EXPRESS OR IMPLIED,
* WITH REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising
* out of the application or use of any product or circuit described herein.
* Cypress does not authorize its products for use as critical components in
* life-support systems where a malfunction or failure may reasonably be
* expected to result in significant injury to the user. The inclusion of
* Cypress' product in a life-support systems application implies that the
* manufacturer assumes all risk of such use and in doing so indemnifies
* Cypress against all charges.
* 
* Use may be limited by and subject to the applicable Cypress software
* license agreement.
* -----------------------------------------------------------------------------
* Copyright (c) Cypress MicroSystems 2000-2003. All Rights Reserved.
*
*****************************************************************************
*  Project Name: UART_Bootloader
*  Project Revision: 1.00
*  Software Version: PSoC Creator 2.2
*  Device Tested: CY8C3866AXI-040
*  Compilers Tested: Keil
*  Related Hardware: CY8CKIT-030
*****************************************************************************
***************************************************************************** */

/*
* Project Description:
* This is a sample bootloader program demonstrating PSoC 5LP bootloading PSoC 3.
* The project is tested using two DVKs - One with PSoC 3 on CY8CKIT-030 and the second one
* with PSoC 5LP on CY8CKIT-050. PSoC 3 must be programmed with this Program.
*
* Connections Required
* CY8CKIT-050 (PSoC 5LP DVK) :
*  P0[0] - Rx -  connected to Tx of PSoC3
*  P0[1] - Tx -  connected to Rx of PSoC3 
*  P6.1 is internally connected to SW1 on DVK.
*
* CY8CKIT-030 (PSoC 3 DVK) : PSoC  3 intially programmed with UART_Bootloader program.
*  P0[0] - Rx - Connected to Tx of PSoC 5LP
*  P0[1] - Tx - Connected to Rx of PSoC 5LP
*  P6.1 is internally connected to SW1 on DVK.
*
* Note that the GNDs of both DVKs should be connected together.
*
* The main()function of this program calls the CyBtldr_Start() API. This API performs the entire bootload operation. 
* It communicates with the host. After a successful bootload operation, this API passes control to the application
* via a software reset.
*
* There are two bootloadable projects: Bootloadable1 (displays “Hello” on char LCD) and Bootloadable2 (displays “Bye” on char LCD). 
* With successive bootload operation, alternate bootloadables will be programmed onto the target. 
*
* The following events happen on each trigger of the switch P6 [1] of CY8CKIT – 050 (PSoC 5LP):
*
* On first switch press, Bootloadable1.cyacd file will be bootloaded onto the target PSoC 3. 
* On successful bootloading the message “Bootloaded - Hello” will be displayed on CY8CKIT – 050 LCD 
* and the message “Hello” will be displayed on CY8CKIT – 030 LCD.
*
* For subsequent bootloading operation press the switch P6 [1] on CY8CKIT – 030. This makes PSoC 3 to enter bootloader 
* and be ready to bootload a new application.
*
* On next switch press on CY8CKIT – 050, Bootloadable2.cyacd file will be bootloaded onto the target PSoC 3. 
* On successful bootloading the message “Bootloaded - Bye” will be displayed on CY8CKIT – 050 LCD and the message “Bye” 
* will be displayed on CY8CKIT – 030 LCD.
***************************************************************************** */

#include <device.h>
#include <stdio.h>

int main()
{
  CyGlobalIntEnable;
  
  //char testString[128];
  //sprintf(testString, "I am the very model of a modern major general");

	/* Initialize PWM */
  PWM_Start();     
  UART_Start();
  
  //UART_PutString(testString);
	
	/* This API does the entire bootload operation. After a succesful bootload operation, this API transfers
	   program control to the new application via a software reset */
	CyBtldr_Start();
	
	/* CyBtldr_Start() API does not return – it ends with a software device reset. So, the code 
	   after this API call (below) is never executed. */
  for(;;)
  {
      
  }
}

void CyBtldrCommStart(void)
{  
  USBUART_Start(0, USBUART_3V_OPERATION);
  while(USBUART_GetConfiguration() == 0)
  {  /* Await the completion of USB configuration */ }
  USBUART_CDC_Init();
}

void CyBtldrCommStop (void)
{
  USBUART_Stop();
}

void CyBtldrCommReset(void)
{
  USBUART_CyBtldrCommReset();
}

cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeOut)
{
  transmitStatusPin_Write(1);
  cystatus retVal = CYRET_TIMEOUT;
  
  *count = 0;
  uint16 internalTimeout = (timeOut*10) + 100;
  uint8 packetsSent = 0;
  uint8 numPackets = size/64;
  uint8 lastPacketSize = size%64;
  /* The sending loop. There are two limits on this:
   1. We can't send data until the prior data transmission is done, so we have
      to wait until USBUART_CDCIsReady() returns a non-zero value.
   2. We can only send 64 bytes at a go.
  */
  while (internalTimeout > 0)
  {
    if (USBUART_CDCIsReady() == 0)
    {
      CyDelay(1);
      --internalTimeout;
      continue;
    }
    /* Once here, we can send out our packets one at a time. There are three
       cases:
     1. More than 64 bytes to send, so do numPackets of 64 bytes followed by one
        packet of lastPacketSize bytes.
     2. 64 bytes to send, so do one packet of 64 bytes, then one packet of zero.
     3. Less than 64 bytes, so do one packet of lastPacketSize bytes.
    */
    else
    {
      if (numPackets > 0)
      {
        USBUART_PutData((buffer+(packetsSent*64)), 64);
        #if 0 
        while(UART_GetTxBufferSize() != 0)
        { /* wait for clear data path on UART */ }
        UART_PutArray((buffer+(packetsSent*64)), 64);
        #endif
        ++packetsSent;
        --numPackets;
        *count += 64;
      }
      else if (numPackets == 0)
      {
        USBUART_PutData((buffer+(packetsSent*64)), lastPacketSize);
        #if 0
        while(UART_GetTxBufferSize() != 0)
        { /* wait for clear data path on UART */ }
        UART_PutArray((buffer+(packetsSent*64)), lastPacketSize);
        #endif
        *count += lastPacketSize;
        retVal = CYRET_SUCCESS;
        break;
      }
    }
  }
  transmitStatusPin_Write(0);
  return retVal;
}

cystatus CyBtldrCommRead (uint8* buffer, uint16 size, uint16* count, uint8 timeOut)
{
  cystatus retVal = CYRET_TIMEOUT;
  if (timeOut) timeOut = 0;
  
  *count = 0;
  uint16 dataAvailableCnt = 0;
  uint16 internalTimeout = 10;
  while (internalTimeout > 0)
  {
    if (USBUART_DataIsReady() == 0)
    {
      CyDelay(1);
      --internalTimeout;
      continue;
    }
    else
    {
      
      receiveStartPin_Write(1);
      dataAvailableCnt = USBUART_GetCount();
      if (dataAvailableCnt > 0) 
      {
      internalTimeout = 2;
      }
      USBUART_GetData((buffer + *count), dataAvailableCnt);
      #if 0
      while(UART_GetTxBufferSize() != 0)
      { /* wait for clear data path on UART */ }
      UART_PutArray((buffer+*count), dataAvailableCnt);
      #endif
      *count += dataAvailableCnt;
      if (*count > 0)
      {
        retVal = CYRET_SUCCESS;
      }
      if (*count >= (size - 1))
      {
        break;
      }
      if (internalTimeout == 0)
      {
        break;
      }
      receiveStartPin_Write(0);
    }
  }
  return retVal;
}
/* [] END OF FILE */