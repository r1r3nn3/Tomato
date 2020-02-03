/// @file light_control.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is used to control the grow lights.

#include <stdio.h>

#include "light_control.h"
#include "display.h"
#include "plant_manager.h"
#include "time_manager.h"

/// @brief Represents the state of the grow light.
bool lightState = false;


/// Initialises the light controler.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void LCinitialise(void){
    lightState = false;
    DSPshow("Initialised: Light control");
}

/// Used to toggle the grow light.
/// @return A event that the grow light is toggled.
event_e LCtoggleLight(void){
    lightState = !lightState;
    if(lightState){
        DSPsimulationSystemInfo("Light state: on", 10000);
    } else {
        DSPsimulationSystemInfo("Light state: off", 10000);
    }
    return E_LIGHT_TOGGLED;
}

/// This function is used to get #lightState.
bool LCgetState(void){
    return lightState;
}

/// This function is used to check the current light state.
/// @return A event that the light needs to be toggled of if the light state is correct.
event_e LClightCheck(void){
    if(LTgetHours() > PTgetLightHours() && lightState){
        return E_LIGHT_TOGGLE;
    } else if(LTgetHours() < PTgetLightHours() && !lightState){
        return E_LIGHT_TOGGLE;
    }
    return E_LIGHT_STATE_OK;
}
