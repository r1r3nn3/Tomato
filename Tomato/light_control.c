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

#include "display.h"
#include "plant.h"
#include "local_time.h"

static bool lightState = 0;

void LCinitialise(void){
    DSPshow("Initialised: Light control");
}

void LCtoggleLight(void){
    lightState = !lightState;
}

bool LCgetState(void){
    return lightState;
}

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
