#ifndef SPI_H
#define SPI_H
#include "STD_MEMORY_MAP.h"
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "ECU_OD.h"
#include "ECU_RM.h"
#include "TMP_SENSOR.h"
#define SS_ENABLE 1
#define SS_DISABLE 0
typedef enum{
	SS_OD=0,
	SS_RM1,
	SS_RM2,
	MAX_SS
}SS_ECU_t;
typedef enum{
	SPI_ENABLE = 0,
	SPI_DISABLE
}SPI_STATE_t;
typedef enum{
	SPI_MASTER = 0,
	SPI_SLAVE
}SPI_MODE_t;
typedef enum{
	SPI_DF4 = 0,
	SPI_DF16,
	SPI_DF64,
	SPI_DF128,
	SPI_DF2,
	SPI_DF8,
	SPI_DF32,
	SPI__DF64
}SPI_DF_t;
typedef enum{
	SPI_INT_DISABLE=0,
	SPI_INT_ENABLE
}SPI_INT_t;
typedef struct{
	UINT8_t Select[MAX_SS];
}SS_t;
extern UINT32_t TMP_Back_Up;
extern UINT8_t SPI_Curr_Reading;
extern SS_t SPI_Slave;
void SPI_Qinit(void);
void SPI_Set_Mode(const SPI_MODE_t MODE);
void SPI_Set_State(const SPI_STATE_t STATE);
void SPI_Set_CLK(const SPI_DF_t DF);
UINT8_t SPI_Tx_Rx(const UINT8_t CHAR);
void SPI_INT(const SPI_INT_t INT);
void SPI_Update(void);
#endif
