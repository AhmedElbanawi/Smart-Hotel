/****************************************************************************/
#ifndef DIO_H
#include "DIO.h"
#endif
/****************************************************************************/
#ifndef KEYPAD_H
#define KEYPAD_H
#define FOUR_X_FOUR 1
#define THREE_X_THREE 2
#define KYPAD_SIZE FOUR_X_FOUR
#define CLOSE 's'
#define CLEAR 'c'
#define RESET 'r'
#define ENTER 'e'
#define KEYPAD_VALUES {{7, 8, 9,'#'}, {4, 5, 6, '#'}, {1, 2, 3, CLOSE}, {CLEAR, 0, RESET, ENTER}}
#define NO_KEY 22
/****************************************************************************/
typedef enum{
	KEYPAD_COL1 = DIO_PINA0,
	KEYPAD_COL2 = DIO_PINA1,
#if KYPAD_SIZE == THREE_X_THREE
	KEYPAD_COL3 = DIO_PINA2
#elif FOUR_X_FOUR
	KEYPAD_COL3 = DIO_PINA2,
	KEYPAD_COL4 = DIO_PINA3
#endif
}KEYPAD_COL_t;
/****************************************************************************/
typedef enum{
	KEYPAD_ROW1 = DIO_PINA4,
	KEYPAD_ROW2 = DIO_PINA5,
#if KYPAD_SIZE == THREE_X_THREE
	KEYPAD_ROW3 = DIO_PINA5
#elif KYPAD_SIZE == FOUR_X_FOUR
	KEYPAD_ROW3 = DIO_PINA6,
	KEYPAD_ROW4 = DIO_PINA7
#endif
}KEYPAD_ROW_t;
/****************************************************************************/
typedef enum{
	KEYPAD_PORT = DIO_PORTA
}KEYPAD_PORT_t;
/****************************************************************************/
#if KYPAD_SIZE == THREE_X_THREE
enum{KEYPAD_MAX_COLS = 3, KEYPAD_MAX_ROWS = 3};
#elif KYPAD_SIZE == FOUR_X_FOUR
enum{KEYPAD_MAX_COLS = 4, KEYPAD_MAX_ROWS = 4};
#endif
/****************************************************************************/
void KEYPAD_Init(void);
/****************************************************************************/
UINT8_t KEYPAD_Read(void);
/****************************************************************************/
#endif
/****************************************************************************/
