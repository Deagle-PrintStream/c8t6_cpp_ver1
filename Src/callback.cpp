
#include "callback.h"
#include "tracer.h"
#include "connectivity.h"

//#include "patrol.h"

/* Private functions defines ---------------------------------------------*/
inline uint8_t min(uint8_t a,uint8_t b){
  return (a<b)?a:b;
}

/* Exported functions definations ---------------------------------------------*/

void tim3_callback(void){
  //direction_t newDir=tracerSelector.update();
  //tracerSelector.update();
  tracer[dirFront].updateData();
}

void tim3_100period_callback(void){
  direction_t testDir=dirFront;
  tracer[testDir].printSensorVal();
  //tracer[testDir].printStatus();
}

void uart1_callback(uint8_t *receiveBuff,uint8_t receiveBuffSize){
  const uint8_t top=min(argCountMax,receiveBuffSize-1);  
  message_t newMsg;
  newMsg.command=(command_t)receiveBuff[0];
  for(uint8_t i=0;i<top;i++){
    newMsg.argList[i]=receiveBuff[i+1];
  }
  receiveCommand(newMsg);
}
