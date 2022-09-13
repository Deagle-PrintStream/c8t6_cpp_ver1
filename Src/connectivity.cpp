
#include "connectivity.h"
/* Exported macro ------------------------------------------------------------*/


/* Exported functions definations ---------------------------------------------*/

HAL_StatusTypeDef sendCommand(message_t &newCmd,const uint8_t argCount){
	uint8_t *newMsg=new uint8_t[argCount+2];
	newMsg[0]=(uint8_t)newCmd.command;
	for(uint8_t i=0;i<argCount;i++){
		newMsg[i+1]=newCmd.argList[i];
	}
	newMsg[argCount+1]=0;
	return HAL_UART_Transmit(&huart1,newMsg,argCount+2,timeoutDefault);
}

void chassisMove(direction_t newDir,uint8_t targetSpeed){
	if(newDir==dirNowhere || newDir==dirAll)
		return;

	message_t newCmd;
	newCmd.command=moveCmd;
	newCmd.argList[0]=(uint8_t)(newDir);
	newCmd.argList[1]=(uint8_t)targetSpeed;
	sendCommand(newCmd,2);
}

void chassisRotate(direction_t newDir,uint8_t targetSpeed){
	if(newDir==dirRight || newDir==dirLeft){
		message_t newCmd;
		newCmd.command=rotateCmd;
		newCmd.argList[0]=(uint8_t)(newDir);
		newCmd.argList[1]=(uint8_t)targetSpeed;
		sendCommand(newCmd,2);
	}
}

void chassisTrim(direction_t newDir,uint8_t trimIntensity){
	if(newDir==dirRight || newDir==dirLeft){
		message_t newCmd;
		newCmd.command=trimCmd;
		newCmd.argList[0]=(uint8_t)(newDir);
		newCmd.argList[1]=(uint8_t)trimIntensity;
		sendCommand(newCmd,2);
	}
}

void chassisStop(uint8_t stopIntensity){
		message_t newCmd;
		newCmd.command=stopCmd;
		newCmd.argList[0]=(uint8_t)(stopIntensity);
		sendCommand(newCmd,1);
}

/* Private functions definations ---------------------------------------------*/


