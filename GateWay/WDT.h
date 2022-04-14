/****************************************************************************/
#ifndef STD_MEMORY_MAP_H
#include "STD_MEMORY_MAP.h"
#endif
/****************************************************************************/
#ifndef WDT_H
#define WDT_H
typedef enum{
	WDT_16_MS = 0,
	WDT_32_MS,
	WDT_65_MS,
	WDT_130_MS,
	WDT_260_MS,
	WDT_520_MS,
	WDT_1000_MS,
	WDT_2100_MS
}WDT_PERIODE_t;
void WDT_Enable(void);
void WDT_Disable(void);
void WDT_Priode(const WDT_PERIODE_t PERIODE);
void WDT_Refresh(void);
void WDT_Qinit(void);
#endif
