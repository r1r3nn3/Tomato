#ifndef LIGHTING_CONTROL_H
#define LIGHTING_CONTROL_H

#include "stdbool.h"

//-----------------Lighting Control-----------------//

void LCinitialise(void);
void LCtoggleLight(void);
bool LCgetState(void);
bool LClightCheck(void);

#endif // LIGHTING_CONTROL_H
