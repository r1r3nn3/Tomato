/// @file file_manager.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @brief This file is used to control the grow lights.

#include <stdio.h>
#include "stdbool.h"

#include "display.h"
#include "plant_manager.h"
#include "time_manager.h"

static bool lightState = false;

/// Initialises the light controler.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void LCinitialise(void){
    DSPshow("Initialised: Light control");
}

/// This function is used to toggle the grow light.
/// @post the #lightState is switched to a different state.
void LCtoggleLight(void){
    lightState = !lightState;
    if(lightState){
        DSPsimulationSystemInfo("Light state: on", 10000);
    } else {
        DSPsimulationSystemInfo("Light state: off", 10000);
    }
}

/// This function is used to get #lightState.
bool LCgetState(void){
    return lightState;
}

/// This function is used to check if #lightState needs to be changed.
bool LClightCheck(void){
    if(LTgetHours() >= PTgetLightHours()){
        if(LCgetState()){
            return true;
        }
    } else {
        if(!LCgetState()){
            return true;
        }
    }
    return false;
}
