#ifndef TMP_SENSOR_H
#define TMP_SENSOR_H
#include "ADC.h"
#define TMP_SENSOR_CHANNEL ADC_CH0
extern UINT32_t TMP_Back_Up;
void TMP_Sensor_Init(void);
UINT32_t TMP_Sensor_Read(void);
void TMP_Update(void);
#endif
