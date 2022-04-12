/***************************************************************************/
#ifndef LCD_H
#include "LCD.h"
#include "util/delay.h"

#define STILL 0
#define ENDED 1
#endif
/*************************************************************************/
static UINT8_t Configuration_Process = STILL, Address_Counter;
/*************************************************************************/
static UINT16_t Reverse_Number(UINT16_t Number); /* Max Number 65535 */
static UINT16_t Get_Number_Length(UINT16_t Number); /* Max Length 5 Digits */
/*************************************************************************/

BOOL_t LCD_Init(void) {
	static UINT8_t Cnt=0;
	BOOL_t IsFinished=FALSE;
	switch(Cnt){
	case 0:

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH); // E should be high
		DIO_WRITE_PIN_VALUE(RW_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  R/W
		DIO_WRITE_PIN_VALUE(RS_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  RS
		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D7

		Cnt=1;
		break;
	case 1:
		Cnt=2;
		break;
	case 2:
		Cnt=3;
		break;
	case 3:
		Cnt=4;
		break;
	case 4:
		if(TRUE==LCD_Send_Command(0X20)){
			Cnt=5;
		}
		break;
	case 5:
		if (TRUE == LCD_Send_Command(0X20)) {
			Cnt = 6;
		}
		break;
	case 6:
		if (TRUE == LCD_Send_Command(0X80)) {
			Cnt = 7;
		}
		break;
	case 7:
		if (TRUE == LCD_Send_Command(0X00)) {
			Cnt = 8;
		}
		break;
	case 8:
		if (TRUE == LCD_Send_Command(0XC0)) {
			Cnt = 9;
		}
		break;
	case 9:
		if (TRUE == LCD_Send_Command(0X00)) {
			Cnt = 10;
		}
		break;
	case 10:
		if (TRUE == LCD_Send_Command(0X10)) {
			Cnt = 11;
		}
		break;
	default:
		Configuration_Process = ENDED;
		Cnt = 0;
		IsFinished = TRUE;
		break;
	}

	return IsFinished;
}
/*************************************************************************/
BOOL_t LCD_Send_Command(const UINT8_t CMD) {
	static UINT8_t Cnt=0;
	BOOL_t IsFinished=FALSE;
	++Cnt;
	if(1==Cnt){
		// Write operation
		DIO_WRITE_PIN_VALUE(RW_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  R/W
		// Command Mode
		DIO_WRITE_PIN_VALUE(RS_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  RS

		// SEND MSB
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E

		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(CMD, 4));   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(CMD, 5));   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(CMD, 6));   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(CMD, 7));   //  D7

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E
	}


	//_delay_ms(10);
	else if (3==Cnt) {
		/* Latch data */
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E

		if (Configuration_Process == ENDED) {
			// SEND LSB
			DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(CMD, 0));   //  D4
			DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(CMD, 1));   //  D5
			DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(CMD, 2));   //  D6
			DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(CMD, 3));   //  D7

			DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E

			//_delay_ms(10);
		}
	}

	// for latching
	//_delay_ms(10);
	else if (5 == Cnt) {
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		Cnt=0;
		IsFinished=TRUE;
	}
	return IsFinished;
}
/*************************************************************************/
void LCD_Disp_Str(const UINT8_t* Data) {

	while (*Data != '\0') {
		LCD_Write_Char(*Data++);
	}

}
/*************************************************************************/
void LCD_Jumb_ToAndWrite(const UINT8_t* Data,
						const LCD_ROW_ID_t ROW,
						const LCD_COL_ID_t COL)
{
	if (ROW < LCD_MAX_ROWS && COL < LCD_MAX_COLS) {
		LCD_Jumb_To(ROW, COL);
		LCD_Disp_Str(Data);
	}

}
/*************************************************************************/
BOOL_t LCD_Jumb_To(const LCD_ROW_ID_t ROW,
				const LCD_COL_ID_t COL)
{
	BOOL_t IsFinished=FALSE;
	/*
	 First Row Start from 0X00
	 Second Row Start From 0X40
	 */
	if (ROW < LCD_MAX_ROWS && COL < LCD_MAX_COLS) {
		Address_Counter = ((0X40 * ROW) + COL) | (1 << 7); // To Write into DDRAM;
		IsFinished=LCD_Send_Command(Address_Counter);
	}
	return IsFinished;
}
/*************************************************************************/
BOOL_t LCD_Write_Char(const UINT8_t Character) {
	static UINT8_t Cnt=0;
	BOOL_t IsFinished=FALSE;
	++Cnt;
	if(1==Cnt){
		// Write operation
		DIO_WRITE_PIN_VALUE(RW_PIN_NUMBER, DIO_PIN_STATE_LOW);     //  R/W
		// Data Mode
		DIO_WRITE_PIN_VALUE(RS_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //   RS

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		// SEND MSB
		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(Character, 4));   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(Character, 5));   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(Character, 6));   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(Character, 7));   //  D7
		/* Latch data */
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E
	}else if (3==Cnt) {
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		// SEN LSB
		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(Character, 0));   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(Character, 1));   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(Character, 2));   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(Character, 3));   //  D7

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E
	}

	//_delay_ms(10);


	//_delay_ms(10);
	/* Latch data */
	else if (5==Cnt) {
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
	}else if (8==Cnt) {
		Cnt=0;
		IsFinished=TRUE;
	}
	return IsFinished;
}
/*************************************************************************/
void LCD_Disp_Number(UINT16_t Number) {
	UINT16_t Length = 0;
	Length = Get_Number_Length(Number);
	Number = Reverse_Number(Number);
	do {
		Length--;
		LCD_Write_Char((UINT8_t) (Number % 10) + '0'); //ex : 101
	} while (Number /= 10);
	while (Length) {
		LCD_Write_Char('0');
		Length--;
	}
}
/*************************************************************************/
BOOL_t LCD_Clear(void){
	BOOL_t IsFinished = FALSE;
	static UINT8_t Cnt = 0;
	switch (Cnt) {
	case 0:
		if (TRUE == LCD_Send_Command(0x00)) {
			Cnt = 1;
		}
		break;
	case 1:
		if (TRUE == LCD_Send_Command(0x01)) {
			Cnt = 2;
		}
		break;
	default:
		Cnt = 0;
		IsFinished = TRUE;
		break;
	}
	return IsFinished;
}
/*************************************************************************/
void LCD_Write_CGRAM(const UINT8_t* Data, CGRAM_ROW_ID_t ROW_ID){
	UINT8_t Address, Idx;
	if(ROW_ID < CGRAM_MAX_ROWS){
		Address = (ROW_ID * 8) | (1 << 6);
		LCD_Send_Command(Address);
		for(Idx = 0; Idx < 8; Idx++){
			LCD_Write_Char(Data[Idx]);
		}
	}
	LCD_Send_Command(0x02);
}
/*************************************************************************/
void LCD_Disp_Special_Character(const CGRAM_ROW_ID_t CGRAM_ROW_ID,
								 const LCD_ROW_ID_t ROW,
								 const LCD_COL_ID_t COL)
{
	if (ROW < LCD_MAX_ROWS && COL < LCD_MAX_COLS && CGRAM_ROW_ID < CGRAM_MAX_ROWS) {
		LCD_Jumb_To(ROW, COL);
		LCD_Write_Char(CGRAM_ROW_ID);
	}

}
/*************************************************************************/
static UINT16_t Reverse_Number(UINT16_t Number) {
	UINT16_t Reversed_Number = 0;
	do {
		Reversed_Number = Reversed_Number * 10 + Number % 10;
	} while (Number /= 10);   //ex : 101
	return Reversed_Number;
}
/*************************************************************************/
static UINT16_t Get_Number_Length(UINT16_t Number) {
	UINT8_t Length = 0;
	do {
		Length++;
	} while (Number /= 10);
	return Length;
}
/*************************************************************************/
BOOL_t LCD_Update(char*Str,LCD_ROW_ID_t ROW, LCD_COL_ID_t COL){
	static UINT8_t State=0, Idx=0;
	BOOL_t IsFinished=FALSE;
	switch (State) {
	case 0:
		if(TRUE==LCD_Init()){
			State=1;
		}
		break;
	case 1:
		if(TRUE==LCD_Jumb_To(ROW,COL)){
			State=2;
		}
		break;
	case 2:
		if (Str[Idx] != '\0') {
			if (TRUE == LCD_Write_Char(Str[Idx])) {
				++Idx;
				if (Str[Idx] == '\0') {
					IsFinished = TRUE;
					Idx=0;
					State=1;
				}
			}
		}
		break;
	default:
		break;

	}
	return IsFinished;
}
void IntToStr(char*Str,UINT8_t Num){
	if (Num / 10) {
		Str[0] = (Num / 10) + '0';
		Str[1] = (Num % 10) + '0';
		Str[2] = '\0';
	} else {
		Str[0] = Num + '0';
		Str[1] = ' ';
		Str[2] = '\0';
	}
}
