
#include "common.h"
#include "tracer.h"
/* Exported macro ------------------------------------------------------------*/

tracer_t tracer[4];

/* Exported functions definens ---------------------------------------------*/


/* Class construction & destruction functions defines ---------------------------------------------*/
/*构造函数*/
tracer_t::tracer_t()\
	:valThrehold(valThreholdDefault),confidenceCoeMax(confidenceCoeMaxDefault)
{
	clearStatus();
	clearValAverage();
	clearValCache();

}

tracer_t::tracer_t(float *confCoeDefaultVal)\
	:valThrehold(valThreholdDefault),confidenceCoeMax(confidenceCoeMaxDefault)
{
	clearStatus();
	clearValAverage();
	clearValCache();
  updateConfCoe(confCoeDefaultVal);

}


/*默认解析函数*/
tracer_t::~tracer_t()
{
	clearStatus();
	clearValAverage();
	clearValCache();
}

/* Class private functions defines ---------------------------------------------*/

void tracer_t::readNewSensorVal(void){
  #define READ_SENSOR_VAL(__order__) \
    ((HAL_GPIO_ReadPin(PIN_SENSOR_##__order__##_GPIO_Port,\
    PIN_SENSOR_##__order__##_Pin))==blackParcel)
  using namespace tracer_nsp;

  newSensorVal[L2]=READ_SENSOR_VAL(0);
  newSensorVal[L1]=READ_SENSOR_VAL(1);
  newSensorVal[M]=READ_SENSOR_VAL(2);
  newSensorVal[R1]=READ_SENSOR_VAL(3);
  newSensorVal[R2]=READ_SENSOR_VAL(4);

  #undef READ_SENSOR_VAL

}

void tracer_t::updateValCache(void){
  for(uint8_t i=0;i<sensorCount;i++){
    valCache[i][valCachePtr]=newSensorVal[i];
  }
  valCachePtr++;
  if(valCachePtr>=valCacheMaxDefault)
    valCachePtr=0;

}

void tracer_t::clearValCache(void){
  for(uint8_t i=0;i<sensorCount;i++){
      for(uint8_t j=0;i<valCacheMaxDefault;i++){
        valCache[i][j]=0;
      }
  }
  valCachePtr=0;
}

void tracer_t::clearValAverage(void){
  for(uint8_t i=0;i<sensorCount;i++){
    newSensorVal[i]=0;
    valAverage[i]=0;
    sensorVal[i]=0;
  }
}

void tracer_t::getValAverage(void)
{  
  for(uint8_t i=0;i<sensorCount;i++){
    valAverage[i]=0;
    for(uint8_t j=0;i<valCacheMaxDefault;i++){
      valAverage[i]+=valCache[i][j];
    }
    valAverage[i]*=(confidenceCoe[i]/confidenceCoeMax);
  }
}

void tracer_t::updateSensorVal(void){
  for(uint8_t i=0;i<sensorCount;i++){
    sensorVal[i]=(valAverage[i]>=valThrehold);
  }
}

void tracer_t::updatePathStatus(void){
  using namespace tracer_nsp;

  status_t preOnPath=onPath;
  if(sensorVal[R1]+sensorVal[M]+sensorVal[L1]==3){
    onPath=1;
  }else{
    onPath=0;
  }

  if(preOnPath==0){
    if(onPath==1){
      hitPath[dirFront]=1;
    }else{
      hitPath[dirFront]=0;
    }
    if(sensorVal[R2]==1){
      hitPath[dirRight]=1;
    }else{
      hitPath[dirRight]=0;
    }
    if(sensorVal[L2]==1){
      hitPath[dirRight]=1;
    }else{
      hitPath[dirRight]=0;
    }
  }else if(preOnPath==1){
    if(onPath==0){
      leavePath[dirFront]=1;
    }else{
      leavePath[dirFront]=0;
    }
    if(sensorVal[R2]==1){
      leavePath[dirLeft]=1;
    }else{
      leavePath[dirLeft]=0;
    }
    if(sensorVal[L2]==1){
      leavePath[dirRight]=1;
    }else{
      leavePath[dirRight]=0;
    }
  }


}

void tracer_t::clearStatus(void)
{
	onPath=0;
	for(uint8_t i=0;i<3;i++){
		hitPath[i]=0;
		leavePath[i]=0;
	}
}

/* Class public functions defines ---------------------------------------------*/

void tracer_t::detectMode(status_t newStatus)
{
  /*默认传入参数为2，即为切换当前模式*/
  if(newStatus>=2){
    detectOn=!detectOn;
  }else{
    detectOn=newStatus;
  }
  clearValCache();
}

void tracer_t::calcStatusMode(status_t newStatus)
{
  /*默认传入参数为2，即为切换当前模式*/
  if(newStatus>=2){
    calcStatus=!calcStatus;
  }else{
    calcStatus=newStatus;
  }
  clearStatus();
}

void tracer_t::updateConfCoe(float *newConfCoeVal){
	if(newConfCoeVal!=nullptr){
		for(uint8_t i=0;i<sensorCount;i++){
			confidenceCoe[i]=newConfCoeVal[i];
		}
	}
}

void tracer_t::updateData(void){
  if(detectOn==on){
    readNewSensorVal();
    updateValCache();
    updateSensorVal();
  }
  if(calcStatus==on){
    updatePathStatus();
  }  
}

void updateTracer(tracer_t &newTracer){
  newTracer.updateData();
}

status_t tracer_t::getPathStatus(hit_leave_t newStatus, direction_t newDir)const{
  using namespace tracer_nsp;
  /*只有3个情况*/
  if(newDir==dirBack || newDir==dirNowhere)
    return (status_t)(-1);

  if(newStatus==leave){
    if(newDir==dirAll){
      return leavePath[dirFront]+leavePath[dirRight]+leavePath[dirLeft];
    }else{
      return leavePath[newDir];
    }
  }else if(newStatus==hit){
    if(newDir==dirAll){
      return hitPath[dirFront]+hitPath[dirRight]+hitPath[dirLeft];
    }else{
      return hitPath[newDir];
    }
  }
  return (status_t)(-1);
}

status_t hittingPath(tracer_t &tracer,direction_t newDir){
  using namespace tracer_nsp;
  return tracer.getPathStatus(hit,newDir);
}

status_t leavingPath(tracer_t &tracer,direction_t newDir){
  using namespace tracer_nsp;
  return tracer.getPathStatus(leave,newDir);
}

__DEBUG void tracer_t::printNewSensorVal(void)const{
  uint8_t newMsg[sensorCount]={0};
  for(uint8_t i=0;i<sensorCount;i++){
    newMsg[i]='0'+newSensorVal[i];
  }
  printMsg(newMsg,sensorCount);
}

__DEBUG void tracer_t::printSensorVal(void)const{
  uint8_t newMsg[sensorCount]={0};
  for(uint8_t i=0;i<sensorCount;i++){
    newMsg[i]='0'+sensorVal[i];
  }
  printMsg(newMsg,sensorCount);
}

__DEBUG void tracer_t::printStatus(void)const{
//想一下怎么方便的输出所有类型的撞线flag
  if(getPathStatus(tracer_nsp::hit,dirAll)){
    uint8_t newMsg[]="hit\t";
    printMsg(newMsg);
    return;
  }
  if(getPathStatus(tracer_nsp::leave,dirAll)){
    uint8_t newMsg[]="leave\t";
    printMsg(newMsg);
    return;
  }
  if(onPath==1){
    uint8_t newMsg[]="on path\t";
    printMsg(newMsg);
  }
}

/* Private functions defines ---------------------------------------------*/





