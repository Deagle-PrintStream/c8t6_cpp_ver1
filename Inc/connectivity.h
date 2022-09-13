
#ifndef __CONNECTIVITY_H
#define __CONNECTIVITY_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Exported constants ------------------------------------------------------------*/
static const uint8_t argCountMax=3;

/* Exported types ------------------------------------------------------------*/

enum command_t{
  errorCmd=0,
  moveCmd=1,
  rotateCmd=2,
  trimCmd=3,
  stopCmd=4,
  pushCurlingCmd=5,
  armRaiseCmd=6,
  detectCodeCmd=7,
  detectCodeAns=8,
  reservedCmd=9,
  testCmd=10,
};

struct message_t{
  command_t command;
  uint8_t argList[argCountMax];
};


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
/*发送指令函数*/
HAL_StatusTypeDef sendCommand(message_t &newCmd,const uint8_t argCount=argCountMax);
/*运动指令*/
void chassisMove(direction_t newDir=dirFront,uint8_t targetSpeed=speedLow);

void chassisRotate(direction_t newDir=dirRight,uint8_t targetSpeed=speedLow);

void chassisTrim(direction_t newDir=dirRight,uint8_t trimIntensity=1);

void chassisStop(uint8_t stopIntensity=1);

/* Private defines -----------------------------------------------------------*/

#define __CONNECTIVITY

#ifdef __cplusplus
}
#endif

#endif	/*__CONNECTIVITY_H*/
