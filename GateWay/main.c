#include "CO_SCH.h"
#include "DIO.h"
#include "SPI.h"
#include "TMP_SENSOR.h"
#include "LCD.h"
#include "DISP.h"
#include "ECU_OD.h"
#include "ECU_RM.h"
#include "WDT.h"

int main(void)
{
	DIO_INIT();
	TMP_Sensor_Init();
	SPI_Qinit();
	WDT_Qinit();
	CO_SCH_Init();
	CO_SCH_Add_Task(SPI_Update, 0, 20);
	CO_SCH_Add_Task(ECU_OD_Update_Info, 0, 20);
	CO_SCH_Add_Task(ECU_RM_Update_Info, 0, 20);
	CO_SCH_Add_Task(DISP_Update, 0, 10);
	CO_SCH_Add_Task(TMP_Update, 0, 20);
	CO_SCH_Add_Task(WDT_Refresh, 0, 100);
	CO_SCH_Start();
	SPI_Update();
	while(1)
	{
		CO_SCH_Dispatch_Tasks();
	}
}
