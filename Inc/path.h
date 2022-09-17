
#ifndef __PATH_H
#define __PATH_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"
#include "patrol.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/



/* Exported constants ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

status_t leaveStartLine(void);

status_t makeTurn(direction_t newDir,plainNode_t newNode,uint32_t timeout);

status_t turnRight(plainNode_t newNode,uint32_t timeout=timeoutDefault);

status_t turnLeft(plainNode_t newNode,uint32_t timeout=timeoutDefault);

status_t goThroughWasteLand(uint32_t timeout=timeoutDefault);

status_t gotoBaseNode(keyNode_t preKeyNode,uint32_t timeout=timeoutDefault);

/*测试寻径函数*/
__DEBUG void testPath(void);

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
