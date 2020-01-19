#ifndef PLANT_H
#define PLANT_H

#include <stdio.h>
#include <stdlib.h>

#define PLANT_NAME_SIZE 20
#define PLANT_MAX_TEMP_MAX 100
#define PLANT_MAX_TEMP_MIN 99
#define PLANT_MAX_WATER_LEVEL 100
#define PLANT_MAX_LIGHT_HOURS 24

typedef struct {
    char name[PLANT_NAME_SIZE];
    int tempMax;
    int tempMin;
    unsigned int waterLevelMax;
    int lightHours;
} plant_t;


//--------------------plant--------------------//

void PTinitialise(plant_t newPlant);
const char * PTgetName(void);
int PTgetTempMax(void);
int PTgetTempMin(void);
unsigned int PTgetWaterLevelMax(void);
int PTgetLightHours(void);
void PTchangePlant(plant_t newPlant);


#endif // PLANT_H
