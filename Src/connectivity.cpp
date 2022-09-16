
#include "connectivity.h"
#include "path.h"

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
	headingDir=newDir;

	message_t newCmd;
	newCmd.command=moveCmd;
	newCmd.argList[0]=(uint8_t)(newDir);
	newCmd.argList[1]=(uint8_t)targetSpeed;
	sendCommand(newCmd,2);
}

void chassisRotate(direction_t newDir,uint8_t targetSpeed){
	if(headingDir!=dirNowhere)
		return;

	if(newDir==dirRight || newDir==dirLeft){
		message_t newCmd;
		newCmd.command=rotateCmd;
		newCmd.argList[0]=(uint8_t)(newDir);
		newCmd.argList[1]=(uint8_t)targetSpeed;
		sendCommand(newCmd,2);
	}
}

void chassisTrim(direction_t newDir,uint8_t trimIntensity){
	if(headingDir==dirNowhere)
		return;
	if(onTrail==0)
		return;

	if(newDir==dirRight || newDir==dirLeft){
		message_t newCmd;
		newCmd.command=trimCmd;
		newCmd.argList[0]=(uint8_t)(newDir);
		newCmd.argList[1]=(uint8_t)trimIntensity;
		sendCommand(newCmd,2);
	}
}

void chassisStop(uint8_t stopIntensity){
	headingDir=dirNowhere;
	
	message_t newCmd;
	newCmd.command=stopCmd;
	newCmd.argList[0]=(uint8_t)(stopIntensity);
	sendCommand(newCmd,1);
}

status_t receiveCommand(message_t newMsg){
	status_t flag=1;
	switch (newMsg.command)
	{
	case errorCmd:
		//errorCmd handler
		flag=0;
		break;
	case detectCodeAns:
		//检测到了正确的条形码，需要进行取壶操作
		break;
	default:
		//unknown cmd handler
		//其余指令本主机均不需要收到
		flag=0;
		break;
	}
	return flag;
}

/* Private functions definations ---------------------------------------------*/


