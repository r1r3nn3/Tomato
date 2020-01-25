/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           21-11-2019
*/

#include <stdio.h>
#include "stdbool.h"
#include "string.h"
#include "stdbool.h"

#include "display.h"
#include "plant_manager.h"

static plant_t currentPlant;

void PTinitialise(plant_t newPlant){
    currentPlant = newPlant;

    DSPshow("Initialised: Plant manager");
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

void PTchangePlant(plant_t newPlant){
    currentPlant = newPlant;
}
