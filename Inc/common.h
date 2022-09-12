
#ifndef __COMMON_H
#define __COMMON_H
/* Private includes ----------------------------------------------------------*/
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

typedef uint8_t status_t;

typedef enum __direction_t{
	dirFront=0,
	dirRight=1,
	dirBack=2,
	dirLeft=3,
	dirNowhere=4,
}direction_t;

typedef enum __on_off_t{
	off=0,
	on=1,
}on_off_t;

namespace tracer_nsp{

	typedef enum __hit_leave_t{
		leave=0,
		hit=1,
	}hit_leave_t;

	typedef enum __sensorOrder_t{
		L2=0,
		L1=1,
		M=2,
		R1=3,
		R2=4,
	}sensorOrder_t;

  static const status_t blackParcel=1;
  static const status_t whiteParcel=0;
}
/* Exported constants ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#define TEMPLATE_API

#ifdef __cplusplus
}
#endif

#endif	/*__COMMON_H*/
