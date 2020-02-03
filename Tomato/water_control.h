#ifndef WATER_CONTROL_H
#define WATER_CONTROL_H

#include "stdbool.h"
#include "events.h"
//-----------------Watering Control-----------------//

void WCinitialise(void);
event_e WCtogglePump(void);
bool WCgetPumpState(void);
event_e WCwateringCheck(void);
unsigned int WCgetPlantWaterLevel(void);
event_e WCwaterPlant(void);
void WCchangeWaterLevel(void);

#endif // WATER_CONTROL_H
