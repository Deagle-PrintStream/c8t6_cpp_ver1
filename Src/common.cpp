
#include "common.h"

/* Exported macro ------------------------------------------------------------*/


/* Exported functions definations ---------------------------------------------*/

HAL_StatusTypeDef printMsg(uint8_t *newMsg,uint8_t msgSize,\
                UART_HandleTypeDef printUart,uint32_t timeout){
    if(sizeof(newMsg)<msgSize)
        msgSize=sizeof(newMsg);
    return HAL_UART_Transmit(&printUart,newMsg,msgSize,timeout);
 }


void Delay_us(uint16_t us)
{
  const uint16_t Delay_Factor_us = HAL_RCC_GetHCLKFreq() / 1000 / 1000; // ought to be defined in .h file
  uint32_t tmp;
  SysTick->LOAD = us * Delay_Factor_us;
  SysTick->VAL = 0x00;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
  do
  {
    tmp = SysTick->CTRL;
  } while (tmp & 0x01 && !(tmp & (1 << 16)));
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL = 0x00;
}



/* Private functions definations ---------------------------------------------*/


