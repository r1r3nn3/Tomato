/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           21-11-2019
*/

#include "fsm.h"
#include "display.h"
#include <stdio.h>
#include "stdbool.h"

int main()
{
    event_e currentEvent = E_START;

    // Update loop
    while(1){
        currentEvent = generateEvent();

        //evenHandler(currentEvent);
        break;
    }

    return 0;
}
