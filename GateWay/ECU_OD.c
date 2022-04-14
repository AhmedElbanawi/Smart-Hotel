#include "ECU_OD.h"
#include "SPI.h"
ECU_OD_DATA_t ECU_OD_Data;
ECU_OD_MODE_t ECU_OD_Mode = ECU_OD_MODE_INFO_ID;
void ECU_OD_Update_Info(void){
	if (SS_ENABLE == SPI_Slave.Select[SS_OD]) {
		switch (ECU_OD_Mode) {
		case ECU_OD_MODE_INFO_ID:
			if (ECU_OD_INFO_ID_CNT == SPI_Curr_Reading) {
				ECU_OD_Mode = ECU_OD_MODE_INFO_CNT;
			} else if (ECU_OD_INFO_ID_TMP == SPI_Curr_Reading) {
				ECU_OD_Mode = ECU_OD_MODE_INFO_TMP;
			} else if (ECU_OD_INFO_ID_LIGHT == SPI_Curr_Reading) {
				ECU_OD_Mode = ECU_OD_MODE_INFO_LIGHT;
			} else {

			}
			break;
		case ECU_OD_MODE_INFO_CNT:
			ECU_OD_Mode = ECU_OD_MODE_INFO_ID;
			ECU_OD_Data.State = SPI_Curr_Reading;
			/*USSUB ROOMS*/
			if(ECU_OD_CNT_OFF==ECU_OD_Data.State)
			{
				ECU_RM_Data[ECU_ROOM1].SubLight = ECU_RM_UNSUB_LIGHT;
				ECU_RM_Data[ECU_ROOM1].SubTemp = ECU_RM_UNSUB_TMP;

				ECU_RM_Data[ECU_ROOM2].SubLight = ECU_RM_UNSUB_LIGHT;
				ECU_RM_Data[ECU_ROOM2].SubTemp = ECU_RM_UNSUB_TMP;
			}
			break;
		case ECU_OD_MODE_INFO_TMP:
			ECU_OD_Mode = ECU_OD_MODE_INFO_ID;
			ECU_OD_Data.Temp = SPI_Curr_Reading;
			break;
		case ECU_OD_MODE_INFO_LIGHT:
			ECU_OD_Mode = ECU_OD_MODE_INFO_ID;
			ECU_OD_Data.Light = SPI_Curr_Reading;
			break;
		default:
			break;
		}

	}
}
