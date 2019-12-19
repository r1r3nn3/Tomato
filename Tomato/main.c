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

int main()
{
    event_e currentEvent = E_START;
    event_e prevEvent;

    DSPsystemInfo();
    DSPhelp();
    DSPserviceInfo();
    /*
    // Update loop
    while(1){
        prevEvent = currentEvent;
        currentEvent = generateEvent();

        evenHandler(currentEvent);
    }
*/
    return 0;
}
