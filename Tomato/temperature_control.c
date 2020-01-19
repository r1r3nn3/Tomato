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
#include "plant.h"

static bool heaterState = false;
static double currentTemperature = 20;


void TCinitialise(void){
    srand(time(NULL));
    DSPshow("Initialised: Temperature control");
}

void TCtoggleHeater(void){
    heaterState = !heaterState;
    if(heaterState){
        DSPsimulationSystemInfo("Heater state: on");
    } else {
        DSPsimulationSystemInfo("Heater state: off");
    }
}

bool TCgetHeaterState(void){
    return heaterState;
}

double TCgetCurrentTemperature(void){
    return currentTemperature;
}

/* -1 is to cold, 0 is oke, 1 is to hot */
int TCtemperatureCheck(void){
    if(currentTemperature > PTgetTempMax()){
        return 1;
    } else if(currentTemperature < PTgetTempMin()){
        return -1;
    }
    return 0;
}

void TCchangeTemperature(void){
    if(heaterState){
        currentTemperature += ((double)(rand() % 100) / 100.0);
    } else {
        currentTemperature += -1 * ((double)(rand() % 100) / 100.0);
    }

}
