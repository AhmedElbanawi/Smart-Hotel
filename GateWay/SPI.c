#include "SPI.h"
#include "DIO.h"
#define MAX_DELAY 23
volatile BOOL_t SPI_Finished = TRUE;
UINT8_t SPI_Curr_Reading;
SS_t SPI_Slave={
					{SS_DISABLE, SS_DISABLE, SS_DISABLE}
};
void SPI_Set_State(const SPI_STATE_t STATE){
	switch (STATE) {
	case SPI_ENABLE:
		SET_BIT(SPCR, SPE);
		break;
	case SPI_DISABLE:
		CLEAR_BIT(SPCR, SPE);
		break;
	}
}
void SPI_Set_Mode(const SPI_MODE_t MODE){
	switch (MODE) {
	case SPI_MASTER:
		SET_BIT(SPCR, MSTR);
		break;
	case SPI_SLAVE:
		CLEAR_BIT(SPCR, MSTR);
		break;
	}
}
void SPI_Set_CLK(const SPI_DF_t DF){
	SPCR &= 0xfc;
	SPCR |= DF;
	SPSR &=0xFE;
	SPSR |=(DF>>2);
}
UINT8_t SPI_Tx_Rx(const UINT8_t CHAR){
	UINT8_t Tmp = SPDR;
	SPDR=CHAR;
	return Tmp;
}
void SPI_INT(const SPI_INT_t INT){
	switch (INT) {
	case SPI_INT_DISABLE:
		CLEAR_BIT(SPCR, 7);
		break;
	case SPI_INT_ENABLE:
		SET_BIT(SPCR, 7);
		break;
	}
}
void SPI_Qinit(void){
	DIO_WRITE_PIN_VALUE(DIO_PINC2, DIO_PIN_STATE_HIGH);/*RM2*/
	DIO_WRITE_PIN_VALUE(DIO_PINC1, DIO_PIN_STATE_HIGH);/*RM1*/
	DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_LOW);/*OD*/

	SPI_Set_CLK(SPI_DF4);
	SPI_Set_Mode(SPI_MASTER);
	SPI_INT(SPI_INT_DISABLE);
	SPI_Set_State(SPI_ENABLE);
}
void SPI_Update(void){
#if 1
	UINT8_t tmp = TMP_Back_Up;
	static SS_ECU_t SlaveSelector=SS_OD;
	static UINT8_t Cnt=0;
	++Cnt;
	switch(SlaveSelector){
	case SS_OD:
		DIO_WRITE_PIN_VALUE(DIO_PINC2, DIO_PIN_STATE_HIGH);/*RM2*/
		DIO_WRITE_PIN_VALUE(DIO_PINC1, DIO_PIN_STATE_HIGH);/*RM1*/
		DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_LOW);/*OD*/

		SPI_Slave.Select[SS_OD]=SS_ENABLE;
		SPI_Slave.Select[SS_RM1]=SS_DISABLE;
		SPI_Slave.Select[SS_RM2]=SS_DISABLE;
		if(MAX_DELAY==Cnt){
			Cnt=0;
			SlaveSelector=SS_RM1;
		}

		break;
	case SS_RM1:
		DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_HIGH);/*OD*/
		DIO_WRITE_PIN_VALUE(DIO_PINC2, DIO_PIN_STATE_HIGH);/*RM2*/
		DIO_WRITE_PIN_VALUE(DIO_PINC1, DIO_PIN_STATE_LOW);/*RM1*/

		SPI_Slave.Select[SS_OD]=SS_DISABLE;
		SPI_Slave.Select[SS_RM1]=SS_ENABLE;
		SPI_Slave.Select[SS_RM2]=SS_DISABLE;

		if (MAX_DELAY == Cnt) {
			Cnt = 0;
			SlaveSelector = SS_RM2;
		}
		break;
	case SS_RM2:
		DIO_WRITE_PIN_VALUE(DIO_PINC0, DIO_PIN_STATE_HIGH);/*OD*/
		DIO_WRITE_PIN_VALUE(DIO_PINC1, DIO_PIN_STATE_HIGH);/*RM1*/
		DIO_WRITE_PIN_VALUE(DIO_PINC2, DIO_PIN_STATE_LOW);/*RM2*/

		SPI_Slave.Select[SS_RM2]=SS_ENABLE;
		SPI_Slave.Select[SS_RM1]=SS_DISABLE;
		SPI_Slave.Select[SS_OD]=SS_DISABLE;
		if (MAX_DELAY == Cnt) {
			SlaveSelector = SS_OD;
			Cnt = 0;
		}

		break;
	default:
		break;
	}
	if (GET_BIT(SPSR, 7)) {
	}
	SPI_Curr_Reading = SPI_Tx_Rx(tmp);
#endif
#if 0
	UINT8_t tmp = TMP_Back_Up;
	if(TRUE == SPI_Finished){
		SPI_Curr_Reading = SPI_Tx_Rx(tmp);
		SPI_Finished = FALSE;
		//DIO_WRITE_PIN_VALUE(DIO_PIND0, 1^DIO_READ_PIN_VALUE(DIO_PIND0));
	}
#endif
}
ISR(SPI_VECT){
	SPI_Finished = TRUE;
}
