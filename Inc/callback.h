
#ifndef __CALLBACK_H
#define __CALLBACK_H

/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/* Exported functions prototypes ---------------------------------------------*/

/*TIM3的中断响应函数*/
extern void tim3_callback(void);
/*TIM3的100个周期的中断响应函数*/
extern void tim3_100period_callback(void);
/*UART1的接收中断函数*/
extern void uart1_callback(uint8_t *receiveBuff,uint8_t receiveBuffSize);

#ifdef __cplusplus
}
#endif

#endif	/*__CALLBACK_H*/
