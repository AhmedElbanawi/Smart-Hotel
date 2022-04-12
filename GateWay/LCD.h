/****************************************************************************/
#ifndef DIO_H
#include "DIO.h"
#endif
/****************************************************************************/
#ifndef LCD_H
#define LCD_H

/*************************************************************************/
#define D4_PIN_NUMBER DIO_PIND0
#define D5_PIN_NUMBER DIO_PIND1
#define D6_PIN_NUMBER DIO_PIND2
#define D7_PIN_NUMBER DIO_PIND3
#define E_PIN_NUMBER  DIO_PIND4
#define RW_PIN_NUMBER DIO_PIND5
#define RS_PIN_NUMBER DIO_PIND6
/*************************************************************************/
typedef enum{
	ROW1 = 0,
	ROW2,
	LCD_MAX_ROWS
}LCD_ROW_ID_t;
/*************************************************************************/
typedef enum{
	COL1 = 0,
	COL2,
	COL3,
	COL4,
	COL5,
	COL6,
	COL7,
	COL8,
	COL9,
	COL10,
	COL11,
	COL12,
	COL13,
	COL14,
	COL15,
	COL16,
	LCD_MAX_COLS
}LCD_COL_ID_t;
/***************************************************************************/
typedef enum{
	CGRAM_ROW1 = 0,
	CGRAM_ROW2,
	CGRAM_ROW3,
	CGRAM_ROW4,
	CGRAM_ROW5,
	CGRAM_ROW6,
	CGRAM_ROW7,
	CGRAM_ROW8,
	CGRAM_MAX_ROWS
}CGRAM_ROW_ID_t;
/***************************************************************************/
BOOL_t LCD_Init(void);
BOOL_t LCD_Send_Command(const UINT8_t CMD);     /* Used To Clear LCD When Send 0X00 */
void LCD_Disp_Str(const UINT8_t* Data);
void LCD_Jumb_ToAndWrite(const UINT8_t* Data,
						const LCD_ROW_ID_t ROW,
						const LCD_COL_ID_t COL);

BOOL_t LCD_Write_Char(const UINT8_t Character);
BOOL_t LCD_Jumb_To(const LCD_ROW_ID_t ROW,
				const LCD_COL_ID_t COL);

void LCD_Write_CGRAM(const UINT8_t* Data, CGRAM_ROW_ID_t ROW_ID);
void LCD_Disp_Special_Character(const CGRAM_ROW_ID_t CGRAM_ROW_ID, const LCD_ROW_ID_t ROW, const LCD_COL_ID_t COL);
BOOL_t LCD_Clear(void);
void LCD_Disp_Number(UINT16_t Number);  /* Use To Write 1, 2, 3, 4 and 5 Digits Max Number 65535 */
/***************************************************************************/
BOOL_t LCD_Update(char*Str,LCD_ROW_ID_t ROW, LCD_COL_ID_t COL);
void IntToStr(char*Str,UINT8_t Num);
#endif
/***************************************************************************/
