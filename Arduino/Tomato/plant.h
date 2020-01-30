#ifndef PLANT_H
#define PLANT_H

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

#endif
