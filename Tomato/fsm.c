/// @file fsm.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @brief This file is related to the finite state machine.

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "string.h"

#include "fsm.h"
#include "display.h"
#include "light_control.h"
#include "temperature_control.h"
#include "water_control.h"
#include "plant_manager.h"
#include "time_manager.h"
#include "keyboard.h"
#include "file_manager.h"

/// @brief Finite state machine states.
///
/// Contains the states used in the finite state machine.
typedef enum {                  /// Error state.
    S_NO,                       /// State at start.
    S_START,                    /// Checking for events state.
    S_CHECK_FOR_EVENT,          /// Handling preveously asked user input in this state.
    S_HANDLE_USER_INPUT,        /// Handling preveously asked service input in this state.
    S_HANDLE_SERVICE_INPUT,     /// The software is initialised in this state.
    S_INITIALISED
} state_e;

/// @brief Used to store the current state off the state machine.
state_e currentState = S_START;
/// @brief Used to store the user action returned from the keyboard.
actions_e userAction = A_NO;

/// @brief Used to store time to be passed.
/// This variable is used to store the time thats needs to be passed.
int timeToPass = 0;

/// Initialises the finite state machine
///
/// This is done at the start of this program. #timeToPass
/// @post This will show a text that the system is initialised.
void FSMinitialise(void){
    DSPshow("Initialised: Finite state machine");
}

/// Because we do not buffer events in an event queue, we send in the
/// current state, #currentState, only events that can be handled.
/// Implementing buffering using a queue and multi-threading is outside
/// the scope of this introduction to C programming.
/// @return Generated event for the #eventHandler function.
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

        // check if there is time to pass
        if(timeToPass != 0){
            evnt = E_PASS_TIME;
            break;
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
        case A_WATER:
        case A_CHANGE:
        case A_ADD:
        case A_USER:
        case A_NO:
        default:
            DSPshow("Invalid input.");
            evnt = E_NON_VALID_INPUT;
            break;
        }

        break;

    case S_HANDLE_SERVICE_INPUT:

        switch(userAction){
        case A_WATER:
            evnt = E_WATER_PLANT;
            break;

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

        case A_UPDATE:
            evnt = E_UPDATE;
            break;

        case A_HELP:
            evnt = E_HELP;
            break;
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


/// Uses the global variable #currentState to determine how to process the
/// received event.
/// If an event is received that should not be in handled in the
/// currentState this is considered as a system error.
/// The switch statements use the default case to show an appropriate message
/// to the display.
/// It is necessary to give in all default cases the nextState an appropriate
/// value to avoid undefined behaviour.
/// @param event This enum is the event that wil be handled in the #currentState.
/// @post Updated #currentState by nextSate.
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
            DSPhelp(0);
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_UPDATE:
            DSPclearScreen();
            DSPsystemInfo(0);
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_SERVICE:
            DSPclearScreen();
            DSPsystemInfo(1);
            userAction = KYBgetAction();
            nextState = S_HANDLE_SERVICE_INPUT;
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
        case E_UPDATE:
            DSPclearScreen();
            DSPsystemInfo(1);
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_HELP:
            DSPhelp(1);
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_WATER_PLANT:
            WCwaterPlant();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_LIGHT_TOGGLE:
            LCtoggleLight();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_HEATER_TOGGLE:
            TCtoggleHeater();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_PUMP_TOGGLE:
            WCtogglePump();
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_CHANGE_PLANT:
            DSPshow("Choose a plant by entering the number before the plant name.");

            int totalPlants = FMgetAmountOfPlants();
            int plantIndex = 0;

            for(int i = 1; i < totalPlants + 1; i++){
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

                if(plantIndex > totalPlants){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }

            FMsetActivePlant(plantIndex);
            PTchangePlant(FMgetPlant(plantIndex));
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_ADD_PLANT:
            ;
            plant_t addPlant;
            int numberBuffer;

            DSPshow("Please enter the name of the plant.");
            strcpy(addPlant.name, KYBgetString());

            int counter = 0;
            while (1) {
                if(addPlant.name[counter] == '\n'){
                    addPlant.name[counter] = '\0';
                    break;
                }
                counter++;
            }

            DSPshow("Please enter the maximum temperature.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_TEMP_MAX);

                if(numberBuffer > PLANT_MAX_TEMP_MAX || numberBuffer < 0){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.tempMax = numberBuffer;

            DSPshow("Please enter the minimum temperature.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_TEMP_MIN);

                if(numberBuffer > PLANT_MAX_TEMP_MIN || numberBuffer < 0){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.tempMin = numberBuffer;

            DSPshow("Please enter the maximum water level.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_WATER_LEVEL);

                if(numberBuffer > PLANT_MAX_WATER_LEVEL || numberBuffer < 0){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.waterLevelMax = numberBuffer;

            DSPshow("Please enter the light hours.");
            while (1) {
                numberBuffer = KYBgetint(PLANT_MAX_LIGHT_HOURS);

                if(numberBuffer > PLANT_MAX_LIGHT_HOURS || numberBuffer < 0){
                    DSPshow("Try again.");
                }else{
                    break;
                }
            }
            addPlant.lightHours = numberBuffer;

            FMsaveNewPlant(addPlant);
            userAction = KYBgetAction();
            switchState = false;
            break;

        case E_USER:
            PTchangePlant(FMgetPlant(FMgetActivePlant()));

            if(WCgetPumpState()){
                WCtogglePump();
            }

            DSPclearScreen();
            DSPsystemInfo(0);
            nextState = S_CHECK_FOR_EVENT;
            break;
        case E_NON_VALID_INPUT:
            userAction = KYBgetAction();
            switchState = false;
            break;

        default:
            DSPshowSystemError("software error in S_HANDLE_SERVICE_INPUT");
            switchState = false;
            break;
        }

        break;

    }

    if(switchState){
        currentState = nextState;
    }
}

/// Initialises all subsystems (devices) and puts an initial text to the
/// display.
/// @return #E_CONTINUE is returned when the inistialisation is done.
event_e TAGinitialise(void){
    DSPinitialise();
    KYBinitialise();
    FSMinitialise();
    LTinitialise();
    FMinitialise();
    PTinitialise(FMgetPlant(FMgetActivePlant()));
    TCinitialise();
    WCinitialise();
    LCinitialise();
    DSPshow("");
    DSPsystemInfo(0);

    return E_CONTINUE;
}

