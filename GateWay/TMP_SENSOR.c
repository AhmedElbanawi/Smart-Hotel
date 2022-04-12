#include "TMP_SENSOR.h"
volatile static BOOL_t ADC_Finished = FALSE;
UINT32_t TMP_Back_Up = 0;
void TMP_Sensor_Init(void){
	ADC_Init();
	ADC_Set_Prescaler(DF128);
	ADC_Interrupt(ENABLE);
	ADC(ENABLE);
	ADC_Conversion(START, TMP_SENSOR_CHANNEL);
}
UINT32_t TMP_Sensor_Read(void){
	SINT32_t Tmp = 0;
	Tmp = ADC_Read();
	Tmp = (((Tmp * 5000) / 1024)) / 10;
	ADC_Conversion(START, TMP_SENSOR_CHANNEL);
	return Tmp;
}
void TMP_Update(void){
	if(TRUE == ADC_Finished){
		TMP_Back_Up = TMP_Sensor_Read();
		ADC_Finished = FALSE;
	}
}
ISR(ADC_VECT){
	ADC_Finished = TRUE;
}
