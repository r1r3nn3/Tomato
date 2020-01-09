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
#include "time.h"

#include "display.h"
#include "local_time.h"
#include "plant.h"

static bool pumpState = false;
static unsigned int plantWaterLevel = 60; // percentage 0 - 100%

static time_t wateringTimer;

void WCinitialise(void){
    srand(time(NULL));
    wateringTimer = LTgetTimeObject();
    DSPshow("Initialised: Water control");
}

void WCtogglePump(void){
    pumpState = !pumpState;
    if(pumpState){
        DSPshow("Pump state: on");
    } else {
        DSPshow("Pump state: off");
    }
}

bool WCgetPumpState(void){
    return pumpState;
}

unsigned int WCgetPlantWaterLevel(void){
    return plantWaterLevel;
}

void WCwaterPlant(void){
    wateringTimer = LTgetTimeObject();
    plantWaterLevel = PTgetWaterLevelMax();
    DSPshow("Watering done");
}

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

void WCchangeWaterLevel(void){
    plantWaterLevel -= (rand() % 10) / 3;
}
