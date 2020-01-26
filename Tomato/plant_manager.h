#ifndef PLANT_MANAGER_H
#define PLANT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>

#define PLANT_NAME_SIZE 20
#define PLANT_MAX_TEMP_MAX 100
#define PLANT_MAX_TEMP_MIN 99
#define PLANT_MAX_WATER_LEVEL 100
#define PLANT_MAX_LIGHT_HOURS 24

/// This struct is used to save the data required for a plant.
typedef struct {                    /// Represends the name of the plant.
    char name[PLANT_NAME_SIZE];     /// Represends the maximum allowed temperature.
    int tempMax;                    /// Represends the minimum allowed temperature.
    int tempMin;                    /// Represends the moisture level in %.
    unsigned int waterLevelMax;     /// Represends the light hours per day.
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
