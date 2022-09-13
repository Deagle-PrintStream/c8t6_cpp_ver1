
#include "common.h"

/* Exported macro ------------------------------------------------------------*/


/* Exported functions definations ---------------------------------------------*/

HAL_StatusTypeDef printMsg(uint8_t *newMsg,uint8_t msgSize,\
                UART_HandleTypeDef printUart,uint32_t timeout){
    if(sizeof(newMsg)<msgSize)
        msgSize=sizeof(newMsg);
    return HAL_UART_Transmit(&printUart,newMsg,msgSize,timeout);
 }

/* Private functions definations ---------------------------------------------*/


