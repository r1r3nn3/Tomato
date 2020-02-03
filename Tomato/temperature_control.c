/// @file temperature_control.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is used to control the temperature.

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "time.h"

#include "temperature_control.h"
#include "display.h"
#include "plant_manager.h"

/// @brief Represents the state of the heater.
bool heaterState = false;

/// @brief Represents the temperature red by the temperature sensor.
double currentTemperature = 10;


/// Initialises the temperature controler.
///
/// This is done at the start of this program.
/// @post A random seed is set changing the temperature. This will show a text that the system is initialised.
void TCinitialise(void){
    srand(time(NULL));
    heaterState = false;
    currentTemperature = 10;
    DSPshow("Initialised: Temperature control");
}


/// This function toggles the heater state.
/// @return A event that the heater state is toggled.
event_e TCtoggleHeater(void){
    heaterState = !heaterState;
    if(heaterState){
        DSPsimulationSystemInfo("Heater state: on", (int)currentTemperature);
    } else {
        DSPsimulationSystemInfo("Heater state: off", (int)currentTemperature);
    }
    return E_HEATER_TOGGLED;
}


/// This function is used to get #heaterState.
bool TCgetHeaterState(void){
    return heaterState;
}


/// This function is used to get #currentTemperature.
double TCgetCurrentTemperature(void){
    return currentTemperature;
}


/// This function is used to check the temperature compered to the heater state.
/// @return A event that represants the if the heater needs to be toggled or if the temperature is dangerousely high.
event_e TCtemperatureCheck(void){
    if(currentTemperature > PLANT_MAX_TEMP_MAX + 10){
        return E_HEATER_ERROR;
    }

    if(currentTemperature > PTgetTempMax() && heaterState){
        return E_HEATER_TOGGLE;
    } else if(currentTemperature < PTgetTempMin() && !heaterState){
        return E_HEATER_TOGGLE;
    }
    return E_HEATER_STATE_OK;
}


/// This function is used to change the #currentTemperature with a random value.
/// The #heaterState dissides if the change is positive or negative.
void TCchangeTemperature(void){
    if(heaterState){
        currentTemperature += ((double)(rand() % 100) / 100.0);
    } else {
        currentTemperature -= ((double)(rand() % 100) / 100.0);
    }

}
