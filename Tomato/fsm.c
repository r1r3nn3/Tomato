/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           21-11-2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "string.h"

#include "fsm.h"
#include "display.h"
#include "light_control.h"
#include "temperature_control.h"
#include "water_control.h"
#include "service_control.h"
#include "plant.h"
#include "local_time.h"

typedef enum {
    S_NO,
    S_START,
    S_WAIT_FOR_EVENT,
    S_WATERING_CONTROL,
    S_TEMPERATURE_CONTROL,
    S_LIGHTING_CONTROL,
    S_SERVICE_MENU,
    S_SELECT_ACTIVE_PLANT_TYPE,
    S_ADD_PLANT_TYPE,
    S_SET_PLANT_NAME,
    S_SET_PLANT_WATER_LEVEL,
    S_SET_PLANT_LIGHT_HOURS,
    S_SET_PLANT_MIN_TEMPERATURE,
    S_SET_PLANT_MAX_TEMPERATURE
} state_e;

static event_e currentEvent = E_NO;
static event_e previousEvent = E_NO;
static state_e currentState = S_START;
static state_e previousState = S_START;

// TODO: get this information from a file
void FSMinitialise(void){
    DSPshow("Initialised: Finite state machine");
}

event_e generateEvent(void)
{
    event_e evnt = E_NO;

    previousEvent = currentEvent;

    switch (currentState)
    {
    case S_NO:
        // TODO: trow error
        break;

    case S_START:
        DSPinitialise();
        PTinitialise();
        FSMinitialise();
        LTinitialise();
        LCinitialise();
        TCinitialise();
        WCinitialise();
        DSPshow("");
        DSPsystemInfo();
        break;

    case S_WAIT_FOR_EVENT:
        // check for correct light state
        if(LClightCheck()){
            evnt = E_LIGHT_TOGGLE;
            break;
        }

        // check if watering is required

        // check if heater needs to be toggled
        if(TCtemperatureCheck() != 0){
            if(TCtemperatureCheck() == -1 && TCgetHeaterState()){
                evnt = E_HEATER_TOGGLE;
                break;
            }
            if(TCtemperatureCheck() == 1 && !TCgetHeaterState()){
                evnt = E_HEATER_TOGGLE;
                break;
            }
        }

        evnt = E_CONTINUE;
        break;

    case S_WATERING_CONTROL:
        WCwaterPlant();
        break;

    case S_TEMPERATURE_CONTROL:
        break;

    case S_LIGHTING_CONTROL:
        break;

    case S_SERVICE_MENU:
        DSPserviceInfo();
        break;

    case S_SELECT_ACTIVE_PLANT_TYPE:
        break;

    case S_ADD_PLANT_TYPE:
        break;

    case S_SET_PLANT_NAME:
        break;

    case S_SET_PLANT_WATER_LEVEL:
        break;

    case S_SET_PLANT_LIGHT_HOURS:
        break;

    case S_SET_PLANT_MIN_TEMPERATURE:
        break;

    case S_SET_PLANT_MAX_TEMPERATURE:
        break;
    }

    return evnt;
}

void eventHandler(event_e event){

    state_e nextState = S_NO;

    switch(currentState){

    default:
        break;
    }
}


/*
E_NO,
E_START,
E_CONTINUE,
E_WATER_PLANT_LOW,
E_WATERING_INTERFALL,
E_WATERING,
E_TEMP_OVER_MAX,
E_TEMP_OVER_MIN,
E_TEMP_ADJUST,
E_LIGHT_ON,
E_LIGHT_OFF,
E_SERVICE_MODE,
E_SERVICE_MODE_OFF,
E_SELLECT_ACTIVE_PLANT,
E_SET_ACTIVE_PLANT,
E_WATER_CONTROL_ON,
E_WATER_CONTROL_OFF,
E_HEATER_ON,
E_HEATER_OFF,
E_ADD_NEW_PLANT,
E_SET_PLANT_NAME,
E_SET_WATER_LEVEL,
E_SET_LIGHT_HOURS,
E_SET_MIN_TEMP,
E_SET_MAX_TEMP,
E_NON_VALID_VALUE,
E_SAVE_NEW_PLANT
*/
