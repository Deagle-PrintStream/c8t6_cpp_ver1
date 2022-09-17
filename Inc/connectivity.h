
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
/*指令类型*/
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
/*通信结构体封装*/
struct message_t{
  command_t command;
  uint8_t argList[argCountMax];
};


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
/*发送指令函数*/
HAL_StatusTypeDef sendCommand(message_t &newCmd,const uint8_t argCount=argCountMax);
/*运动指令*/
void chassisMoveCmd(direction_t newDir=dirFront,uint8_t targetSpeed=speedLow);
/*原地旋转指令*/
void chassisRotateCmd(direction_t newDir=dirRight,uint8_t targetSpeed=speedLow);
/*行进中微调方向指令*/
void chassisTrimCmd(direction_t newDir=dirRight,uint8_t trimIntensity=1);
/*停止运动指令*/
void chassisStopCmd(uint8_t stopIntensity=1);
/*接收指令*/
status_t receiveCommand(message_t newMsg);

/* Private defines -----------------------------------------------------------*/

#define __CONNECTIVITY

#ifdef __cplusplus
}
#endif

#endif	/*__CONNECTIVITY_H*/
