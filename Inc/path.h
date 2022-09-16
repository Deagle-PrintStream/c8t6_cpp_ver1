
#ifndef __PATH_H
#define __PATH_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/



/* Exported constants ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Class defines -----------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/

/*当前运动方向，dirNowhere即停止不动*/
extern uint8_t headingDir;
/*当前是否预设地在路线上，即曲线部分跳过时，需要手动置为0*/
extern status_t onTrail;

#define __PATH

#ifdef __cplusplus
}
#endif

#endif	/*__PATH_H*/
