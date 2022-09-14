
#include "path.h"

/* Exported macro ------------------------------------------------------------*/

selector_t tracerSelector;
patrol_t patrol;

/* Exported functions defines ---------------------------------------------*/


/* Private functions defines ---------------------------------------------*/

/* Class functions defines ---------------------------------------------*/

/*Selector_t functions defines---------------------------------------------*/

selector_t::selector_t(){
	currDir=(uint8_t)dirFront;
}

selector_t::~selector_t(){

}

void selector_t::updateOutput(void)const{
	#define SELECTOR_OUTPUT(__outA,__outB) do{\
		HAL_GPIO_WritePin(PIN_SELECTOR_0_GPIO_Port,PIN_SELECTOR_0_Pin,__outA);\
		HAL_GPIO_WritePin(PIN_SELECTOR_1_GPIO_Port,PIN_SELECTOR_1_Pin,__outB);\
	}while(0)
	#define ON GPIO_PIN_SET
	#define OFF GPIO_PIN_RESET

	/*TODO:校对selector的输出引脚数值*/
	switch ((direction_t)currDir){
	case dirFront:
		SELECTOR_OUTPUT(ON,ON);
		break;
	case dirRight:
		SELECTOR_OUTPUT(ON,OFF);
		break;
	case dirBack:
		SELECTOR_OUTPUT(OFF,OFF);
		break;
	case dirLeft:
		SELECTOR_OUTPUT(OFF,ON);
		break;
	default:
		break;
	}

	#undef SELECTOR_OUTPUT
	#undef ON
	#undef OFF
}

void selector_t::setCurrDir(direction_t newDir){
	currDir=(uint8_t)newDir;
	updateOutput();
}

direction_t selector_t::update(void){
	if(currDir<dirBack){
		currDir++;
	}else{
		currDir=dirFront;
	}
	updateOutput();
	return (direction_t)currDir;
}

void updateSelector(selector_t &selector){
	selector.update();
}

/*patrol_t functions defines---------------------------------------------*/
patrol_t::patrol_t(){
	currPlainNode=nowhere;
	preKeyNode=startLine;
	updateOn=tracer_nsp::off;
}

patrol_t::~patrol_t(){
	currPlainNode=nowhere;
	preKeyNode=startLine;
}

void patrol_t::updatePlainNode(void){
	#define PLAIN_NODE_SET(__front,__right,__left,__back,__node) do{\
		if(onPath[dirFront]==__front &&onPath[dirRight]==__right &&\
			onPath[dirLeft]==__left &&onPath[dirBack]==__back ){\
				currPlainNode=__node;\
				return;}\
	}while(0)

	status_t onPath[directionCount];
	for(uint8_t i=0;i<4;i++){
		onPath[i]=tracer[i].onPath;
	}
	/*TODO:更改为组合成一个uint8_t类型，每一位表示一个tracer.onPath，直接进行数值判断,但是keil中无法表示二进制*/
	PLAIN_NODE_SET(0,0,0,0,nowhere);
	PLAIN_NODE_SET(1,0,0,0,frontOnly);
	PLAIN_NODE_SET(0,0,1,0,backOnly);
	PLAIN_NODE_SET(0,1,0,0,rightOnly);
	PLAIN_NODE_SET(0,0,0,1,leftOnly);
	PLAIN_NODE_SET(1,0,1,0,straightLine);
	PLAIN_NODE_SET(0,1,0,1,horizontalLine);
	PLAIN_NODE_SET(0,1,1,0,rightTurn);
	PLAIN_NODE_SET(0,0,1,1,leftTurn);
	PLAIN_NODE_SET(1,1,1,0,rightFork);
	PLAIN_NODE_SET(1,0,1,1,leftFork);
	PLAIN_NODE_SET(0,1,1,1,T_crossing);
	PLAIN_NODE_SET(1,1,1,1,crossing);

	#undef PLAIN_NODE_SET

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
	/*根据前一个节点和目标节点，调用不同的巡线函数，待完成*/
	/*TODO:*/
}

