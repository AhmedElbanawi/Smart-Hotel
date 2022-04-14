#ifndef DISP_H
#define DISP_H
#include "LCD.h"
#include "ECU_OD_COMM_CFG.h"
#include "ECU_RM_COMM_CFG.h"
#include "TMP_SENSOR.h"
extern ECU_OD_DATA_t ECU_OD_Data;
void DISP_Init(void);
void DISP_Update(void);
#endif
