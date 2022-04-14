#include "ECU_RM.h"
#include "SPI.h"
ECU_RM_DATA_t ECU_RM_Data[MAX_ECU_RM];
ECU_RM_INFO_t ECU_RM_Info = ECU_RM_OFF;
static void ECU_RM_Update(ECU_RM_t ROOM);
void ECU_RM_Update_Info(void){
	if (SS_ENABLE == SPI_Slave.Select[SS_RM1]) {
		/*update reading&writing*/
		ECU_RM_Update(ECU_ROOM1);
	} else if (SS_ENABLE == SPI_Slave.Select[SS_RM2]) {
		ECU_RM_Update(ECU_ROOM2);
	} else {

	}
}
static void ECU_RM_Update(ECU_RM_t ROOM){

	switch (SPI_Curr_Reading) {
	case ECU_RM_OFF:
		ECU_RM_Data[ROOM].SubLight = ECU_RM_UNSUB_LIGHT;
		ECU_RM_Data[ROOM].SubTemp = ECU_RM_UNSUB_TMP;
		ECU_RM_Data[ROOM].State = ECU_RM_OFF;
		break;
	case ECU_RM_ON:
		ECU_RM_Data[ROOM].State = ECU_RM_ON;
		break;
	case ECU_RM_SUB_LIGHT:
		ECU_RM_Data[ROOM].SubLight = ECU_RM_SUB_LIGHT;
		break;
	case ECU_RM_SUB_TMP:
		ECU_RM_Data[ROOM].SubTemp = ECU_RM_SUB_TMP;
		break;
	case ECU_RM_UNSUB_LIGHT:
		ECU_RM_Data[ROOM].SubLight = ECU_RM_UNSUB_LIGHT;
		break;
	case ECU_RM_UNSUB_TMP:
		ECU_RM_Data[ROOM].SubTemp = ECU_RM_UNSUB_TMP;
		break;
	default:
		break;
	}


}
