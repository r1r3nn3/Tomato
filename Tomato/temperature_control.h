#ifndef TEMPERATURE_CONTROL_H
#define TEMPERATURE_CONTROL_H

#include "stdbool.h"
#include "events.h"

//----------------Temperature Control----------------//

void TCinitialise(void);
event_e TCtoggleHeater(void);
bool TCgetHeaterState(void);
double TCgetCurrentTemperature(void);
void TCchangeTemperature(void);
event_e TCtemperatureCheck(void);

#endif // TEMPERATURE_CONTROL_H
