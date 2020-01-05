/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           21-11-2019
*/

// TODO: is this required??

#include <stdio.h>
#include "stdbool.h"
#include "string.h"
#include "stdbool.h"

#include "display.h"
#include "plant.h"

static plant_t currentPlant;

void PTinitialise(void){
    strcpy(currentPlant.name, "Tomato");
    currentPlant.tempMax = 25;
    currentPlant.tempMin = 15;
    currentPlant.waterLevelMax = 80;
    currentPlant.lightHours = 8;
    DSPshow("Initialised: Plant");
}

const char * PTgetName(){
    return currentPlant.name;
}

int PTgetTempMax(){
    return currentPlant.tempMax;
}

int PTgetTempMin(){
    return currentPlant.tempMin;
}

unsigned int PTgetWaterLevelMax(){
    return currentPlant.waterLevelMax;
}

int PTgetLightHours(){
    return currentPlant.lightHours;
}
