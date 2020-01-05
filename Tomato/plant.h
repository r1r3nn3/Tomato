#ifndef PLANT_H
#define PLANT_H

#include <stdio.h>
#include <stdlib.h>

//--------------------plant--------------------//

void PTinitialise(void);
const char * PTgetName(void);
int PTgetTempMax(void);
int PTgetTempMin(void);
unsigned int PTgetWaterLevelMax(void);
int PTgetLightHours(void);

typedef struct {
    char name[20];
    int tempMax;
    int tempMin;
    unsigned int waterLevelMax;
    int lightHours;
} plant_t;

#endif // PLANT_H
