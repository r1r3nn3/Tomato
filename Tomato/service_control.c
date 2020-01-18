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

bool serviceMode = false;


void SCinitialise(void){
    DSPshow("Initialised: Service mode.");
}

bool SCgetServiceState(void){
    return serviceMode;
}
