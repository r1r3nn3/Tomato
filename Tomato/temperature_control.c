/// @file temperature_control.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @brief This file is used to control the temperature.

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "time.h"

#include "display.h"
#include "plant_manager.h"

static bool heaterState = false;
static double currentTemperature = 10;

/// Initialises the temperature controler.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void TCinitialise(void){
    srand(time(NULL));
    DSPshow("Initialised: Temperature control");
}

/// This function is used to toggle the heater.
/// @post the #heaterState is switched to a different state.
void TCtoggleHeater(void){
    heaterState = !heaterState;
    if(heaterState){
        DSPsimulationSystemInfo("Heater state: on", (int)currentTemperature);
    } else {
        DSPsimulationSystemInfo("Heater state: off", (int)currentTemperature);
    }
}

/// This function is used to get #heaterState.
bool TCgetHeaterState(void){
    return heaterState;
}

/// This function is used to get #currentTemperature.
double TCgetCurrentTemperature(void){
    return currentTemperature;
}


/// This function is used to check if #lightState needs to be changed.
/// @return The return value represents the following: -1 = to cold, 0 = oke, 1 = to hot.
int TCtemperatureCheck(void){
    if(currentTemperature > PTgetTempMax()){
        return 1;
    } else if(currentTemperature < PTgetTempMin()){
        return -1;
    }
    return 0;
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
