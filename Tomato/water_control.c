/// @file water_control.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is used to control the water level off the plant.

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "time.h"

#include "water_control.h"
#include "display.h"
#include "time_manager.h"
#include "plant_manager.h"

/// @brief Represents the state off the pump.
bool pumpState = false;
/// @brief Represents the soil moisture in percentage red by a sensor.
unsigned int plantWaterLevel = 0;


/// Initialises the water controler.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void WCinitialise(void){
    pumpState = false;
    srand(time(NULL));
    DSPshow("Initialised: Water control");
}

/// This function toggles the pump.
/// @return A event that the pump has been toggled.
event_e WCtogglePump(void){
    pumpState = !pumpState;
    if(pumpState){
        DSPsimulationSystemInfo("Pump state: on", (int)plantWaterLevel);
    } else {
        DSPsimulationSystemInfo("Pump state: off", (int)plantWaterLevel);
    }
    return E_PUMP_TOGGLED;
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
/// @return A event that the plant is watered.
event_e WCwaterPlant(void){
    int tempPlantWaterLevel = (int)plantWaterLevel;
    plantWaterLevel = PTgetWaterLevelMax();
    DSPsimulationSystemInfo("Watering done", tempPlantWaterLevel);
    return E_WATERED_PLANT;
}

/// This function checks if watering is required.
/// @return A event that the plant is watered.
event_e WCwateringCheck(void){
    if(plantWaterLevel <= PTgetWaterLevelMax() / 3){
        // watering on sensor
        return E_WATER_PLANT;
    }

    return E_PLANT_WATER_OK;
}

/// This function is used to decrease the #plantWaterLevel with a random value.
void WCchangeWaterLevel(void){
    plantWaterLevel -= (rand() % 10) / 3;
}
