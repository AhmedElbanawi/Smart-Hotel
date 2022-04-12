#include "DISP.h"
ECU_RM_DATA_t ECU_RM_Tmp_Data[MAX_ECU_RM];
ECU_OD_DATA_t ECU_OD_Tmp_Data;
void DISP_Update(void){
	static char StrTemp[3];
#if 0
	static UINT8_t Cnt=0;
	++Cnt;
	if(10==Cnt){
		Cnt = 0;
		LCD_Jumb_To(ROW1,COL7);
		LCD_Write_Char(' ');
		LCD_Jumb_To(ROW1,COL6);
		LCD_Disp_Number(ECU_OD_Data.Temp);

		//LCD_Jumb_ToAndWrite("light: ", ROW2, COL1);
		switch (ECU_OD_Data.Light) {
		case ECU_OD_LIGHT_MORNING:
			LCD_Jumb_ToAndWrite("M", ROW2, COL8);
			break;
		case ECU_OD_LIGHT_NIGHT:
			LCD_Jumb_ToAndWrite("N", ROW2, COL8);
			break;
		default:
			break;
		}
		if (ECU_RM_Data[0].SubLight == ECU_RM_SUB_LIGHT
				&& ECU_RM_Data[0].SubTemp == ECU_RM_SUB_TMP) {
			LCD_Jumb_ToAndWrite("TL", ROW1, COL15);
		} else if (ECU_RM_Data[0].SubLight == ECU_RM_SUB_LIGHT) {
			LCD_Jumb_ToAndWrite("L ", ROW1, COL15);
		} else if (ECU_RM_Data[0].SubTemp == ECU_RM_SUB_TMP) {
			LCD_Jumb_ToAndWrite("T ", ROW1, COL15);
		} else {
			LCD_Jumb_ToAndWrite("  ", ROW1, COL15);
		}

	}
#endif
	static UINT8_t State = 0;
	switch (State) {
	case 0:
		if (TRUE == LCD_Update("tmp:", ROW1, COL1)) {
			State = 1;
		}
		break;
	case 1:
		if (TRUE == LCD_Update("RM1:", ROW1, COL9)) {
			State = 2;
		}
		break;
	case 2:
		if (TRUE == LCD_Update("Light:", ROW2, COL1)) {
			State = 3;
		}
		break;
	case 3:
		if (TRUE == LCD_Update("RM2:", ROW2, COL9)) {
			State = 4;
		}
		break;
	case 4:
		ECU_RM_Tmp_Data[ECU_ROOM1].SubLight=ECU_RM_Data[ECU_ROOM1].SubLight;
		ECU_RM_Tmp_Data[ECU_ROOM1].SubTemp=ECU_RM_Data[ECU_ROOM1].SubTemp;

		ECU_RM_Tmp_Data[ECU_ROOM2].SubLight=ECU_RM_Data[ECU_ROOM2].SubLight;
		ECU_RM_Tmp_Data[ECU_ROOM2].SubTemp=ECU_RM_Data[ECU_ROOM2].SubTemp;

		ECU_OD_Tmp_Data.Light=ECU_OD_Data.Light;
		ECU_OD_Tmp_Data.Temp=ECU_OD_Data.Temp;
		ECU_OD_Tmp_Data.State=ECU_OD_Data.State;

		IntToStr(StrTemp, ECU_OD_Tmp_Data.Temp);
		if (TRUE == LCD_Update(StrTemp, ROW1, COL5)) {
			State = 5;
		}
		break;
	case 5:
		if (ECU_OD_LIGHT_MORNING == ECU_OD_Tmp_Data.Light) {
			if (TRUE == LCD_Update("M", ROW2, COL7)) {
				State = 6;
			}
		} else if (ECU_OD_LIGHT_NIGHT == ECU_OD_Tmp_Data.Light) {
			if (TRUE == LCD_Update("N", ROW2, COL7)) {
				State = 6;
			}
		} else {
			if (TRUE == LCD_Update(" ", ROW2, COL7)) {
				State = 6;
			}
		}
		break;
	case 6:
		if (ECU_RM_Tmp_Data[ECU_ROOM1].SubLight == ECU_RM_SUB_LIGHT
				&& ECU_RM_Tmp_Data[ECU_ROOM1].SubTemp == ECU_RM_SUB_TMP) {
			if (TRUE == LCD_Update("TL", ROW1, COL13)) {
				State = 7;
			}
		} else if (ECU_RM_Tmp_Data[ECU_ROOM1].SubLight == ECU_RM_SUB_LIGHT) {
			if (TRUE == LCD_Update("L ", ROW1, COL13)) {
				State = 7;
			}
		} else if (ECU_RM_Tmp_Data[ECU_ROOM1].SubTemp == ECU_RM_SUB_TMP) {
			if (TRUE == LCD_Update("T ", ROW1, COL13)) {
				State = 7;
			}
		} else {
			LCD_Update("  ", ROW1, COL13);
			State = 7;
		}
		break;
	case 7:
		if (ECU_RM_Tmp_Data[ECU_ROOM2].SubLight == ECU_RM_SUB_LIGHT
				&& ECU_RM_Tmp_Data[ECU_ROOM2].SubTemp == ECU_RM_SUB_TMP) {
			if (TRUE == LCD_Update("TL", ROW2, COL13)) {
				State = 0;
				//DIO_WRITE_PIN_VALUE(DIO_PINC6,1^DIO_READ_PIN_VALUE(DIO_PINC6));
			}
		} else if (ECU_RM_Tmp_Data[ECU_ROOM2].SubLight == ECU_RM_SUB_LIGHT) {
			if (TRUE == LCD_Update("L ", ROW2, COL13)) {
				State = 0;
				DIO_WRITE_PIN_VALUE(DIO_PINC6,1^DIO_READ_PIN_VALUE(DIO_PINC6));
			}
		} else if (ECU_RM_Tmp_Data[ECU_ROOM2].SubTemp == ECU_RM_SUB_TMP) {
			if (TRUE == LCD_Update("T ", ROW2, COL13)) {
				State = 0;
			//	DIO_WRITE_PIN_VALUE(DIO_PINC6,1^DIO_READ_PIN_VALUE(DIO_PINC6));
			}
		} else {
			LCD_Update("  ", ROW2, COL13);
			State = 0;
		}
		break;
	default:
		State = 0;
		break;
	}

}
