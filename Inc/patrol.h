
#ifndef __PATROL_H
#define __PATROL_H

/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
	

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

class selector_t{
private:
  /*当前选择器返回值对应的的tracer*/
  uint8_t currDir;

  /*根据当前方向设置gpio输出*/
  void updateOutput(void)const;
public:
  selector_t();
  ~selector_t();

  /*手动设置当前选择器对应返回值*/
  void setCurrDir(direction_t newDir=dirFront);
  /*周期性更新返回值,时钟周期中断里直接调用该函数即可*/
  direction_t update(void);
  friend void updateSelector(selector_t &selector);

};
	
class patrol_t{
private:
  /*当前平凡节点，即直线或者右转弯等*/
	plainNode_t currPlainNode;
  /*当前关键节点，如起跑线或者取壶点等*/
	keyNode_t preKeyNode;
  /*是否开启检测*/
	status_t updateOn;
  /**/
  /**/
  /**/
  /**/
public:

	patrol_t();
	~patrol_t();
  /*根据四个tracer的数值更新当前所在平凡节点类型*/
	void updatePlainNode(void);
  /*开启或者关闭节点检测*/
	void switchMode(status_t newMode=tracer_nsp::off);
  /*强制设置平凡检点类型*/
	void setPlainNode(plainNode_t newPlainNode=nowhere);
  /*强制设置关键检点类型*/
	void setKeyNode(keyNode_t newKeyNode=startLine);
  /*检测到指定平凡节点*/
    status_t detectPlainNode(plainNode_t newNode)const;
    friend status_t detectNode(patrol_t &patrol,plainNode_t newNode);

  /*从preNode出发向newNode行进，整合了各个部分的运动方向*/
	void headingFor(keyNode_t newKeyNode,uint32_t timeout=timeoutMax)const;

};

extern selector_t tracerSelector;
extern patrol_t patrol;

#define __PATROL

#ifdef __cplusplus
}
#endif

#endif	/*__PATROL_H*/
