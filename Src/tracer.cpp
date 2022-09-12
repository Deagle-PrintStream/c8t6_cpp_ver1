
#include "common.h"
#include "tracer.h"
/* Exported macro ------------------------------------------------------------*/


/* Exported functions definens ---------------------------------------------*/


/* Class private functions defines ---------------------------------------------*/

void tracer_t::readNewSensorVal(void){
  #define READ_SENSOR_VAL(__order__) \
    ((HAL_GPIO_ReadPin(PIN_SENSOR_##__order__##_GPIO_Port,\
    PIN_SENSOR_##__order__##_Pin))==blackParcel)
  using namespace tracerRelated;

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

void tracer_t::getValAverage(void)
{  
  for(uint8_t i=0;i<sensorCount;i++){
    valAverage[i]=0;
    for(uint8_t j=0;i<valCacheMaxDefault;i++){
      valAverage[i]+=valCache[i][j];
    }
  }
}

void tracer_t::updateSensorVal(void){
  for(uint8_t i=0;i<sensorCount;i++){
    sensorVal[i]=(valAverage[i]>=valThrehold);
  }
}

void tracer_t::updatePathStatus(void){
  using namespace tracerRelated;

  if(sensorVal[R1]+sensorVal[M]+sensorVal[L1]==3){
    onPath=1;
  }else{
    onPath=0;
  }

}

/* Class public functions defines ---------------------------------------------*/

void tracer_t::updateConfCoe(uint8_t *newConfCoeVal){
	if(newConfCoeVal!=nullptr){
		for(uint8_t i=0;i<sensorCount;i++){
			confidenceCoe[i]=newConfCoeVal[i];
		}
	}

}


void updateTracer(tracer_t &newTracer){
  newTracer.readNewSensorVal();
  newTracer.updateValCache();
  newTracer.updatePathStatus();
  newTracer.updateSensorVal();
}

/* Private functions defines ---------------------------------------------*/





