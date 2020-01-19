#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

//-----------------File Manager-----------------//

#define PATH_MAX 260

#include "plant.h"

void FMinitialise(void);
void FMwriteToLog(int messageType, const char *text);
plant_t FMgetPlant(int plantIndex);
const char * FMgetPlantName(int plantIndex);
void FMsaveNewPlant(plant_t newPlant);
void FMsetActivePlantLocation(void);
int FMgetActivePlant(void);
int FMgetAmountOfPlants(void);
void FMsetActivePlant(int index);

#endif // FILE_MANAGER_H
