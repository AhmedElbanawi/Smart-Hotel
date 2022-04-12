#ifndef ECU_OD_CFG_H
#define ECU_OD_CFG_H

typedef enum{
	ECU_OD_INFO_ID_CNT=0,
	ECU_OD_INFO_ID_TMP,
	ECU_OD_INFO_ID_LIGHT
}ECU_OD_INFO_ID_t;
typedef enum{
	ECU_OD_MODE_INFO_ID=0,
	ECU_OD_MODE_INFO_CNT,
	ECU_OD_MODE_INFO_TMP,
	ECU_OD_MODE_INFO_LIGHT
}ECU_OD_MODE_t;
enum{
	ECU_OD_CNT_OFF=0,
	ECU_OD_CNT_ON,
	ECU_OD_LIGHT_MORNING,
	ECU_OD_LIGHT_NIGHT
};
typedef struct{
	UINT8_t Temp,Light,State;
}ECU_OD_DATA_t;
#endif
