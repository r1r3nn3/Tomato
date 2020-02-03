#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

//-----------------File Manager-----------------//

#define PATH_MAX 260

#include "plant_manager.h"
#include "events.h"
void FMinitialise(void);
void FMwriteToLog(int messageType, const char *text);
plant_t FMgetPlant(unsigned int plantIndex);
const char * FMgetPlantName(int plantIndex);
event_e FMsaveNewPlant(plant_t newPlant);
int FMgetActivePlant(void);
int FMgetAmountOfPlants(void);
void FMsetActivePlant(int index);

#endif // FILE_MANAGER_H
