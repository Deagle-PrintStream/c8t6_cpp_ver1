
#include "callback.h"
#include "tracer.h"
#include "patrol.h"

void tim3_callback(void){
  //direction_t newDir=tracerSelector.update();
  tracerSelector.update();
  tracer[dirFront].updateData();
}

void tim3_100period_callback(void){
  direction_t testDir=dirFront;
  tracer[testDir].printNewSensorVal();
  //tracer[testDir].printSensorVal();
  //tracer[testDir].printStatus();
}

