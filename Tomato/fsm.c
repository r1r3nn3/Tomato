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
#include "keyboard.h"
#include "file_manager.h"

typedef enum {
    S_NO,
    S_START,
    S_CHECK_FOR_EVENT,
    S_HANDLE_USER_INPUT,
    S_HANDLE_SERVICE_INPUT,
    S_INITIALISED
} state_e;

static state_e currentState = S_START;
static actions_e userAction = A_NO;

static int timeToPass = 0;

void FSMinitialise(void){
    DSPshow("Initialised: Finite state machine");
}


event_e generateEvent(void)
{
    event_e evnt = E_NO;

    switch (currentState)
    {
    case S_NO:
        DSPshowSystemError("software error S_NO");
        break;

    case S_START:
        evnt = TAGinitialise();
        break;

    case S_INITIALISED:
        evnt = E_CONTINUE;

    case S_CHECK_FOR_EVENT:
        // check if there is time to pass
        if(timeToPass != 0){
            evnt = E_PASS_TIME;
            break;
        }

        // check for correct light state
        if(LClightCheck()){
            evnt = E_LIGHT_TOGGLE;
            break;
        }

        // check if watering is required
        if(WCwateringCheck()){
            evnt = E_WATER_PLANT;
            break;
        }

        // check if heater needs to be toggled
        int tempCheck = TCtemperatureCheck();
        bool tempState = TCgetHeaterState();
        if(tempCheck != 0){
            if(tempCheck == -1 && !tempState){
                evnt = E_HEATER_TOGGLE;
                break;
            }
            if(tempCheck == 1 && tempState){
                evnt = E_HEATER_TOGGLE;
                break;
            }
        }

        // if the plant is take care of ask for user input
        evnt = E_ASK_USER_INPUT;
        break;

    case S_HANDLE_USER_INPUT:

        switch(userAction){
        case A_HELP:
            evnt = E_HELP;
            break;

        case A_SERVICE:
            evnt = E_SERVICE;
            break;

        case A_TIME:
            evnt = E_INCREASE_TIME;
            break;

        case A_UPDATE:
            evnt = E_UPDATE;
            break;

        // not a valid input in this state
        case A_LIGHT:
        case A_HEATER:
        case A_PUMP:
        case A_CHANGE:
        case A_ADD:
        case A_NO:
        default:
            DSPshow("Invalid input.");
            evnt = E_NON_VALID_INPUT;
            break;
        }

        break;

    case S_HANDLE_SERVICE_INPUT:

        switch(userAction){
        case A_LIGHT:
            evnt = E_LIGHT_TOGGLE;
            break;

        case A_HEATER:
            evnt = E_HEATER_TOGGLE;
            break;

        case A_PUMP:
            evnt = E_PUMP_TOGGLE;
            break;

        case A_CHANGE:
            evnt = E_CHANGE_PLANT;
            break;

        case A_ADD:
            evnt = E_ADD_PLANT;
            break;

        case A_USER:
            evnt = E_USER;
            break;

        case A_HELP:
        case A_SERVICE:
        case A_TIME:
        case A_NO:
        default:
            DSPshow("Invalid input.");
            evnt = E_NON_VALID_INPUT;
            break;
        }
        break;
    }

    return evnt;
}

void eventHandler(event_e event){

    state_e nextState = S_NO;
    bool switchState = true;

    switch (currentState)
    {
    case S_NO:
        DSPshowSystemError("software error S_NO");
        break;

    case S_START:
        nextState = S_INITIALISED;
        break;

    case S_INITIALISED:
        nextState = S_CHECK_FOR_EVENT;
        break;

    case S_CHECK_FOR_EVENT:
        switch(event){

        case E_PASS_TIME:
            if(timeToPass >= 30){
                LTincreaseTime(30);
                timeToPass -= 30;
            } else {
                LTincreaseTime(timeToPass);
                timeToPass = 0;
            }
            TCchangeTemperature();
            WCchangeWaterLevel();
            switchState = false;
            break;

        case E_LIGHT_TOGGLE:
            LCtoggleLight();
            switchState = false;
            break;

        case E_HEATER_TOGGLE:
            TCtoggleHeater();
            switchState = false;
            break;

        case E_WATER_PLANT:
            WCwaterPlant();
            switchState = false;
            break;

        case E_ASK_USER_INPUT:
            userAction = KYBgetAction();
            nextState = S_HANDLE_USER_INPUT;
            break;

        default:
            DSPshowSystemError("software error in S_CHECK_FOR_EVENT");
            break;

        }

        break;

    case S_HANDLE_USER_INPUT:

        switch(event){

        case E_INCREASE_TIME:
            DSPshow("Enter the time in minutes to be passed like this 'xxx'.");

            int buffer;
            while (1) {
                buffer= KYBgetint(1000);

                if(buffer >= 1000){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }

            timeToPass += buffer;
            nextState = S_CHECK_FOR_EVENT;
            break;

        case E_HELP:
            DSPhelp();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_UPDATE:
            DSPclearScreen();
            DSPsystemInfo();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_SERVICE:
            DSPserviceInfo();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_NON_VALID_INPUT:
            userAction = KYBgetAction();
            switchState = false;
            break;

        default:
            DSPshowSystemError("software error in S_HANDLE_USER_INPUT");
            switchState = false;
            break;

        }
    break;


    case S_HANDLE_SERVICE_INPUT:

        switch(event){

        case E_LIGHT_TOGGLE:
            LCtoggleLight();
            switchState = false;
            break;

        case E_HEATER_TOGGLE:
            TCtoggleHeater();
            switchState = false;
            break;

        case E_PUMP_TOGGLE:
            WCtogglePump();
            switchState = false;
            break;

        case E_CHANGE_PLANT:
            DSPshow("Choose a plant by entering the number before the plant name.");

            int totalPlants = FMgetAmountOfPlants();
            int plantIndex = 0;

            for(int i = 1; i < totalPlants; i++){
                char printBuffer[PLANT_NAME_SIZE + 5];
                char buffer[5];

                itoa(i, buffer, 10);
                strcpy(printBuffer, buffer);
                (i < 10) ? strcat(printBuffer, "  - ") : strcat(printBuffer, " - ");
                strcat(printBuffer, FMgetPlantName(i));

                DSPshow(printBuffer);
            }

            while (1) {
                plantIndex = KYBgetint(1000);

                if(plantIndex < totalPlants){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }

            FMsetActivePlant(plantIndex);
            PTchangePlant(FMgetPlant(plantIndex));
            switchState = false;
            break;

        case E_ADD_PLANT:
            ;
            plant_t addPlant;
            int numberBuffer;

            DSPshow("Please enter the name of the plant.");
            strcpy(addPlant.name, KYBgetString());

            DSPshow("Please enter the maximum temperature.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_TEMP_MAX);

                if(numberBuffer < PLANT_MAX_TEMP_MAX || 0 < numberBuffer){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.tempMax = numberBuffer;

            DSPshow("Please enter the minimum temperature.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_TEMP_MIN);

                if(numberBuffer < PLANT_MAX_TEMP_MIN || 0 < numberBuffer){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.tempMin = numberBuffer;

            DSPshow("Please enter the maximum water level.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_WATER_LEVEL);

                if(numberBuffer < PLANT_MAX_WATER_LEVEL || 0 < numberBuffer){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.waterLevelMax = numberBuffer;

            DSPshow("Please enter the light hours.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_LIGHT_HOURS);

                if(numberBuffer < PLANT_MAX_LIGHT_HOURS || 0 < numberBuffer){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.lightHours = numberBuffer;

            FMsaveNewPlant(addPlant);
            switchState = false;
            break;

        case E_USER:
            PTchangePlant(FMgetPlant(FMgetActivePlant()));
            DSPclearScreen();
            DSPsystemInfo();
            nextState = S_CHECK_FOR_EVENT;
            break;

        default:
            DSPshowSystemError("software error in S_HANDLE_SERVICE_INPUT");
            break;
        }

        break;

    }

    if(switchState){
        currentState = nextState;
    }
}

event_e TAGinitialise(void){
    DSPinitialise();
    FSMinitialise();
    LTinitialise();
    LCinitialise();
    FMinitialise();
    PTinitialise(FMgetPlant(FMgetActivePlant()));
    TCinitialise();
    WCinitialise();
    DSPshow("");
    DSPsystemInfo();

    return E_CONTINUE;
}

