#ifndef TEMPERATURE_CONTROL_H
#define TEMPERATURE_CONTROL_H

#include "stdbool.h"

//----------------Temperature Control----------------//

void TCinitialise(void);
void TCtoggleHeater(void);
bool TCgetHeaterState(void);
double TCgetCurrentTemperature(void);
void TCchangeTemperature(void);
int TCtemperatureCheck(void);

#endif // TEMPERATURE_CONTROL_H
