#ifndef ECU_RM_COMM_CFG_H
#define ECU_RM_COMM_CFG_H
#define MAX_ECU_RM 2
typedef struct{
	UINT8_t Temp,Light,State,SubLight,SubTemp;
}ECU_RM_DATA_t;
typedef enum{
	ECU_RM_OFF=11,
	ECU_RM_ON=12,
	ECU_RM_SUB_TMP=13,
	ECU_RM_SUB_LIGHT=14,
	ECU_RM_UNSUB_TMP=15,
	ECU_RM_UNSUB_LIGHT=16
}ECU_RM_INFO_t;
typedef enum{
	ECU_ROOM1=0,
	ECU_ROOM2,
	ECU_MAX_ROOMS
}ECU_RM_t;
typedef enum{
	ECU_FRM_TMP=0x00,
	ECU_FRM_USUB=0x40,
	ECU_FRM_NIGHT=0x80,
	ECU_FRM_MORNING=0xc0
}ECU_RM_WF_t;

extern ECU_RM_DATA_t ECU_RM_Data[MAX_ECU_RM];
extern ECU_RM_INFO_t ECU_RM_Info;
#endif
