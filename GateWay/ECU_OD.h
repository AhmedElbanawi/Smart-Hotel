#ifndef ECU_OD_H
#define ECU_OD_H
#include "STD_MEMORY_MAP.h"
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "ECU_OD_COMM_CFG.h"
extern ECU_OD_DATA_t ECU_OD_Data;
extern UINT8_t SPI_Curr_Reading;
void ECU_OD_Update_Info(void);
#endif
