/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           25-01-2020
*/

#include "fsm.h"

/// Executes the state machine (FSM: Finite State Machine) in
/// an endless loop processing the generated event by a subsystem.
/// The state machine is excuted by the function #eventHandler.
/// @author Alwin Rodewijk
/// @date 24-01-2020

int main()
{
    event_e currentEvent = E_START;

    // Endless loop
    while(1){
        currentEvent = generateEvent();
        eventHandler(currentEvent);
    }

    return 0;
}
