/// @file water_control.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is used to control the water level off the plant.

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "time.h"

#include "display.h"
#include "time_manager.h"
#include "plant_manager.h"

/// @brief Represents the state off the pump.
bool pumpState = false;
/// @brief Represents the soil moisture in percentage red by a sensor.
unsigned int plantWaterLevel = 0;

time_t wateringTimer;

/// Initialises the water controler.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void WCinitialise(void){
    srand(time(NULL));
    wateringTimer = LTgetTimeObject();
    DSPshow("Initialised: Water control");
}

/// This function is used to toggle the pump.
/// @post the #pumpState is switched to a different state.
void WCtogglePump(void){
    pumpState = !pumpState;
    if(pumpState){
        DSPsimulationSystemInfo("Pump state: on", (int)plantWaterLevel);
    } else {
        DSPsimulationSystemInfo("Pump state: off", (int)plantWaterLevel);
    }
}

/// This function is used to get #pumpState.
bool WCgetPumpState(void){
    return pumpState;
}

/// This function is used to get the #plantWaterLevel.
unsigned int WCgetPlantWaterLevel(void){
    return plantWaterLevel;
}

/// This function is used to water the plant.
/// @post The plant is watered to the maximum water level off the current plant.
void WCwaterPlant(void){
    wateringTimer = LTgetTimeObject();
    int tempPlantWaterLevel = (int)plantWaterLevel;
    plantWaterLevel = PTgetWaterLevelMax();
    DSPsimulationSystemInfo("Watering done", tempPlantWaterLevel);
}

/// This function checks if watering is required.
bool WCwateringCheck(void){
    bool returnValue = false;

    if(wateringTimer + (PTgetWaterLevelMax() * 60) <= LTgetTimeObject()){
        // watering on timer
        returnValue = true;
    }

    if(plantWaterLevel <= PTgetWaterLevelMax() / 3){
        // watering on sensor
        returnValue = true;
    }

    return returnValue;
}

/// This function is used to decrease the #plantWaterLevel with a random value.
void WCchangeWaterLevel(void){
    plantWaterLevel -= (rand() % 10) / 3;
}
