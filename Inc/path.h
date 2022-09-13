
#ifndef __PATH_H
#define __PATH_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/*平凡节点，即路程中的任意节点类型，四个传感器返回值的排列组合*/
enum plainNode_t{
  nowhere=0,
  frontOnly=1,
  backOnly=2,
  rightOnly=3,
  leftOnly=4,
  straightLine=5,
  horizontalLine=6,
  rightTurn=7,
  leftTurn=8,
  rightFork=9,
  leftFork=10,
  T_crossing=11,
  crossing=12,
};

/*关键节点，即巡线模块的定位节点*/
enum keyNode_t{
  startLine=0,
  upperRightTurning=1,
  lowerRightTurning=2,
  baseNode=3,
  crossroadLeft=4,
  crossroadMid=5,
  crossroadRight=6,
  curlingDepositEasy=7,
  curlingDepositHard=8, 
  launchNode=9,
  lostInNowhere=(uint8_t)(-1),

};


/* Exported constants ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

/* Class defines -----------------------------------------------------------*/

class patrol_t{
private:
	plainNode_t currPlainNode;
	keyNode_t preKeyNode;

	status_t updateOn;


public:

	patrol_t();
	~patrol_t();

	void updatePlainNode(void);
	void switchMode(status_t newMode=tracer_nsp::off);
	void setPlainNode(plainNode_t newPlainNode=nowhere);
	void setKeyNode(keyNode_t newKeyNode=lostInNowhere);
	void headingFor(keyNode_t newKeyNode,uint32_t timeout=timeoutMax)const;



};
patrol_t::patrol_t(){
	currPlainNode=nowhere;
	preKeyNode=startLine;
	updateOn=tracer_nsp::off;
}

patrol_t::~patrol_t(){
	currPlainNode=nowhere;
	preKeyNode=startLine;
}

#define __PATH

#ifdef __cplusplus
}
#endif

#endif	/*__PATH_H*/
