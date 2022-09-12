
#ifndef __TRACER_H
#define __TRACER_H
/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/



/* Exported constants ------------------------------------------------------------*/
static const uint8_t sensorCount=5;
static const uint8_t valCacheMaxDefault=5;
static const uint8_t valThreholdDefault=3;
static const uint8_t confidenceCoeMaxDefault=1;

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#define TEMPLATE_API

/* Class defines -----------------------------------------------------------*/

class tracer_t{
private:
	const uint8_t valThrehold;
	const uint8_t confidenceCoeMax;

	/*瞬时测得的传感器数值*/
	status_t newSensorVal[sensorCount];
	/*传感器数值缓冲区,累计计数前若干此传感数值，得到一个时期内的平均值，
	即valCache[i]/valCacheMax 为该点的对外使用数值 */
	uint8_t valCache[sensorCount][valCacheMaxDefault];
	/*cache的指针，为队列形式，一个周期后覆盖原先的数值*/
	uint8_t valCachePtr;
	/*传感器历史数值的平均值= valAverage[i]/valThrehold */
	uint8_t valAverage[sensorCount];
	/*传感器数值是否超过阈值，若是则视为在黑线上*/
	status_t sensorVal[sensorCount];
	/*每一个传感器的置信系数，目前设置为0/1，即可信或者不可信，
	根据初始状态自动进行设置，下一步可以根据行进过程中动态调节其置信比*/
	uint8_t confidenceCoe[sensorCount];

	/*读入新的传感器数值*/
	void readNewSensorVal(void);
	/*更新每个传感器数值的缓存区*/
	void updateValCache(void);
	/*清空缓存区*/
	void clearValCache(void);
	/*取得近一段时间内的平均值*/
	void getValAverage(void);
	/*计算是否超过了阈值，即平均时间内的二值化*/
	void updateSensorVal(void);

	/*更新tracer的路径检测数值，包括onPath,hitPath,leavePath*/
	void updatePathStatus(void);
	
public:
	/*根据valCache计算得到的若干关于该tracer的统计值*/
	/*该tracer是否在线上*/
	status_t onPath;
	/*该tracer是否刚从线外进入到线上*/
	status_t hitPath;
	/*该tracer是否刚从线上离开到线外*/
	status_t leavePath;

	tracer_t(uint8_t *confCoeDefaultVal);
	~tracer_t();
	/*更新置信系数，即过程中是否存在传感器失灵的情况*/
	void updateConfCoe(uint8_t *newConfCoeVal);
	/*更新tracer所有数值*/
	friend void updateTracer(tracer_t &newTracer);
};

/* Class construction & destruction functions defines ---------------------------------------------*/
tracer_t::tracer_t(uint8_t *confCoeDefaultVal=nullptr)\
	:valThrehold(valThreholdDefault),confidenceCoeMax(confidenceCoeMaxDefault)
{
	for(uint8_t i=0;i<sensorCount;i++){
		newSensorVal[i]=0;
		sensorVal[i]=0;
		for(uint8_t j=0;i<valCacheMaxDefault;j++)
			valCache[i][j]=0;

	}
	if(confCoeDefaultVal!=nullptr){
		for(uint8_t i=0;i<sensorCount;i++){
			confidenceCoe[i]=confCoeDefaultVal[i];
		}
	}
	valCachePtr=0;

	onPath=0;
	hitPath=0;
	leavePath=0;

}

tracer_t::~tracer_t()
{
}

#ifdef __cplusplus
}
#endif

#endif	/*__TRACER_H*/
