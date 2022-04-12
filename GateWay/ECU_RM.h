#ifndef ECU_RM_H
#define ECU_RM_H
#include "STD_MEMORY_MAP.h"
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "ECU_RM_COMM_CFG.h"
extern UINT8_t SPI_Curr_Reading;
extern ECU_RM_INFO_t ECU_RM_Info;
void ECU_RM_Update_Info(void);
#endif
