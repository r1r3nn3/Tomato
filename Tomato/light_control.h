#ifndef LIGHTING_CONTROL_H
#define LIGHTING_CONTROL_H

#include "stdbool.h"
#include "events.h"

//-----------------Lighting Control-----------------//

void LCinitialise(void);
event_e LCtoggleLight(void);
bool LCgetState(void);
event_e LClightCheck(void);

#endif // LIGHTING_CONTROL_H
