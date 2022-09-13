
#ifndef __COMMON_H
#define __COMMON_H
/* Private includes ----------------------------------------------------------*/
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported constants ------------------------------------------------------------*/

static const uint8_t msgSizeDefault=10;
static const uint32_t timeoutDefault=0x00ff;
static const uint32_t timeoutMax=0x0ffffffff;
static const uint8_t speedHigh=100;
static const uint8_t speedLow=10;




/* Exported types ------------------------------------------------------------*/
/*状态类型*/

/*方向类型*/
enum direction_t{
	dirFront=0,
	dirRight=1,
	dirLeft=2,
	dirBack=3,	
	dirNowhere=4,
	dirAll=5,
};

typedef uint8_t status_t;

/*tracer相关的类型*/
namespace tracer_nsp{
	enum on_off_t{
		off=0,
		on=1,
	};
	enum hit_leave_t{
		leave=0,
		hit=1,
	};

	enum sensorOrder_t{
		L2=0,
		L1=1,
		M=2,
		R1=3,
		R2=4,
	};
  static const status_t blackParcel=1;
  static const status_t whiteParcel=0;
}


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
extern UART_HandleTypeDef huart1;
/*自定义的调试输出函数，不能像printf一样输出更多类型的数值*/
extern HAL_StatusTypeDef printMsg(uint8_t *newMsg,uint8_t msgSize=msgSizeDefault,\
								UART_HandleTypeDef printUart=huart1,uint32_t timeout=timeoutDefault);

/* Private defines -----------------------------------------------------------*/

/*__USED is unable to download into the chip*/
/*__STATIC_FORCEINLINE is not so necessary*/

/*调试用函数标记*/
#define __DEBUG

#ifdef __cplusplus
}
#endif

#endif	/*__COMMON_H*/
