#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include "stdbool.h"

//-----------------Watering Control-----------------//

void WCinitialise(void);
void WCtogglePump(void);
bool WCgetPumpState(void);
bool WCwateringCheck(void);
unsigned int WCgetPlantWaterLevel(void);
void WCwaterPlant(void);
void WCchangeWaterLevel(void);

#endif // WATER_CONTROL_H
