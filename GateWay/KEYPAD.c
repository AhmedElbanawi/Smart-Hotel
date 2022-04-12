/****************************************************************************/
#ifndef KEYPAD_H
#include "KEYPAD.h"
/****************************************************************************/
void KEYPAD_Init(void){
	UINT8_t Idx;
	KEYPAD_COL_t KYPAD_Col[KEYPAD_MAX_COLS] = {KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3};
#if KYPAD_SIZE == FOUR_X_FOUR
	KYPAD_Col[3] = KEYPAD_COL4;
#endif
	for(Idx = 0; Idx < KEYPAD_MAX_COLS; Idx++){
		DIO_WRITE_PIN_VALUE(KYPAD_Col[Idx], DIO_PIN_STATE_HIGH);
	}
}
/****************************************************************************/
UINT8_t KEYPAD_Read(void){
	UINT8_t Col_Idx, Row_Idx, Key_Pressed = NO_KEY;
	KEYPAD_COL_t KYPAD_Col[KEYPAD_MAX_COLS] = {KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3};
	KEYPAD_ROW_t KEYPAD_Row[KEYPAD_MAX_ROWS] = {KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3};
	UINT8_t Keypad[KEYPAD_MAX_ROWS][KEYPAD_MAX_COLS] = KEYPAD_VALUES;
#if KYPAD_SIZE == FOUR_X_FOUR
	KYPAD_Col[3] = KEYPAD_COL4;
	KEYPAD_Row[3] = KEYPAD_ROW4;
#endif
	for(Col_Idx = 0; Col_Idx < KEYPAD_MAX_COLS; Col_Idx++){
		DIO_WRITE_PIN_VALUE(KYPAD_Col[Col_Idx], DIO_PIN_STATE_LOW);
		for(Row_Idx = 0; Row_Idx < KEYPAD_MAX_ROWS; Row_Idx++){
			if(DIO_PIN_STATE_LOW == DIO_READ_PIN_VALUE(KEYPAD_Row[Row_Idx])){
				Key_Pressed = Keypad[Row_Idx][Col_Idx];
				while(DIO_PIN_STATE_LOW == DIO_READ_PIN_VALUE(KEYPAD_Row[Row_Idx]));
				DIO_WRITE_PIN_VALUE(KYPAD_Col[Col_Idx], DIO_PIN_STATE_HIGH);
				return Key_Pressed;
			}
		}
		DIO_WRITE_PIN_VALUE(KYPAD_Col[Col_Idx], DIO_PIN_STATE_HIGH);
	}
	return Key_Pressed;
}
/****************************************************************************/
#endif
/****************************************************************************/
