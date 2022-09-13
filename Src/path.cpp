
#include "path.h"

/* Exported macro ------------------------------------------------------------*/


/* Exported functions definations ---------------------------------------------*/


/* Private functions definations ---------------------------------------------*/



void patrol_t::updatePlainNode(void){
	status_t onPath[4];
	for(uint8_t i=0;i<4;i++){
		
	}
}

void patrol_t::switchMode(status_t newMode){
    updateOn=newMode;
}

void patrol_t::setPlainNode(plainNode_t newPlainNode){
    currPlainNode=newPlainNode;
}

void patrol_t::setKeyNode(keyNode_t newKeyNode){
    preKeyNode=newKeyNode;
}

void patrol_t::headingFor(keyNode_t newKeyNode,uint32_t timeout)const{

}

