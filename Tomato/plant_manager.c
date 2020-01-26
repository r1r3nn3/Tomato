/// @file plant_manager.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @brief This file is used to manage the currently active plant.

#include <stdio.h>
#include "stdbool.h"
#include "string.h"
#include "stdbool.h"

#include "display.h"
#include "plant_manager.h"

static plant_t currentPlant;

/// Initialises the plant manager.
///
/// This is done at the start of this program.
/// @param[in] newPlant A plant_t struc used to set the #currentPlant.
void PTinitialise(plant_t newPlant){
    currentPlant = newPlant;

    DSPshow("Initialised: Plant manager");
}

/// This function is used to get the name of the the current active plant.
/// @return A pointer to a string containing the name of the current active plant.
const char * PTgetName(){
    return currentPlant.name;
}

/// This function is used to get the maximum temperature of the the current active plant.
/// @return A int containing the maximum temperature of the current active plant.
int PTgetTempMax(){
    return currentPlant.tempMax;
}

/// This function is used to get the minimum temperature of the the current active plant.
/// @return A int containing the minimum temperature of the current active plant.
int PTgetTempMin(){
    return currentPlant.tempMin;
}

/// This function is used to get the maximum allows water level of the the current active plant.
/// @return A int containing the maximum allows water level of the current active plant.
unsigned int PTgetWaterLevelMax(){
    return currentPlant.waterLevelMax;
}

/// This function is used to get the light hours per day of the the current active plant.
/// @return A int containing the light hours per day of the current active plant.
int PTgetLightHours(){
    return currentPlant.lightHours;
}

/// This function is used to get the light hours per day of the the current active plant.
/// @param[in] newPlant A plant_t struc used to set the #currentPlant.
void PTchangePlant(plant_t newPlant){
    currentPlant = newPlant;
}
