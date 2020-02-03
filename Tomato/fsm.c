/// @file fsm.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
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

/// @brief A enum used for the states in the finite state machine
typedef enum {
    /// Error state, should never be reached.
    S_NO,
    /// State at the start of this program.
    S_START,
    /// Program is initialised in this state.
    S_INITIALISE,
    /// The operation mode will be checked in this state.
    S_CHECK_OPERATION_MODE,
    /// Check if time is to be passed.
    S_CHECK_TIME_TO_PASS,
    /// Time will be passed in ths state.
    S_PASS_TIME,
    /// The light state will be checked, if after toggling the state is still not correct a error will be generated.
    S_CHECK_LIGHT_STATE,
    /// The grow light will be toggled in this state.
    S_TOGGLE_LIGHT,
    /// The heater state will be checked, if after toggling the state is still not correct a error will be generated.
    S_CHECK_HEATER_STATE,
    /// The heater state will be toggled in this state.
    S_TOGGLE_HEATER,
    /// The water level will be checked,  if after watering the plant the state is still not correct a error will be generated.
    S_CHECK_WATER_LEVEL,
    /// The plant will be watered in this state.
    S_WATER_PLANT,
    /// There will be checked if there is more time to be passed.
    S_CHECK_MORE_TIME_TO_PASS,
    /// There will be waited for a input from the user and than handled in the next state.
    S_WAIT_FOR_USER_INPUT,
    /// The system info will be updated.
    S_UPDATE_USER_SYSTEM_INFO,
    /// The user menu will be printed.
    S_PRINT_USER_HELP,
    /// The service menu will be printed.
    S_PRINT_SERVICE_HELP,
    /// The time will be increased according to user input.
    S_INCREASE_TIME,
    /// Wait for service user input.
    S_WAIT_FOR_SERVICE_INPUT,
    /// The pump state will be toggled in this state.
    S_SERVICE_TOGGLE_PUMP,
    /// The heater state will be toggled in this state.
    S_SERVICE_TOGGLE_HEATER,
    /// The light state will be toggled in this state.
    S_SERVICE_TOGGLE_LIGHT,
    /// The plant will be watered in this state.
    S_SERVICE_WATER_PLANT,
    /// The system will be updated for service mode in this state.
    S_UPDATE_SERVICE_SYSTEM_INFO,
    /// There will be asked to set a new active plant according to the saved plants in plants.csv.
    S_ASK_FOR_NEW_ACTIVE_PLANT,
    /// There will be asked to input the parameters required for a #plant_t to be saved in plants.csv.
    S_ASK_NEW_PLANT_INFO,
    /// A error state where the system will be reset.
    S_ERROR
} state_e;

/// @brief A enum used for the operator mode.
typedef enum {
    /// User mode.
    M_USER,
    /// Service mode.
    M_SERVICE
} operating_mode_e;


/// @brief Used to store the current state off the state machine.
state_e currentState = S_START;
/// @brief Used to store the user action returned from the keyboard.
actions_e userAction = A_NO;

/// @brief Used to store time to be passed.
/// This variable is used to store the time thats needs to be passed.
int timeToPass = 0;

/// @brief Used to store time active plant index.
/// This variable is used to store the active plant index which is used in the state machine.
int plantIndex;

/// @brief Used to store the total amount of plants.
/// This variable is used to store the total amount of plants saved which is used in the state machien.
int totalPlants;

/// @brief Used to store a new plant to be added.
/// This variable is used to store the time thats needs to be passed.
plant_t addPlant;

/// @brief Used to store a error message to be printed in the #S_ERROR state.
/// This variable is used to store a error message to be printed in the #S_ERROR state.
char errorMessage[DISPLAY_SIZE];

/// @brief Used to store the current operating mode.
/// This variable is used to store the current operating mode.
operating_mode_e currentOperatingMode = M_USER;


/// Initialises the finite state machine
///
/// This is done at the start of this program. #timeToPass
/// @post This will show a text that the system is initialised.
void FSMinitialise(void){
    plantIndex = FMgetActivePlant();
    totalPlants = FMgetAmountOfPlants();
    DSPshow("Initialised: Finite state machine");
}


/// Because we do not buffer events in an event queue, we send in the
/// current state, #currentState, only events that can be handled.
/// Implementing buffering using a queue and multi-threading is outside
/// the scope of this introduction to C programming.
/// @return Generated event for the #eventHandler function.
event_e generateEvent(void){
    event_e evnt = E_NO;


    switch(currentState){
    case(S_NO):
        DSPshowSystemError("S_NO");
        break;


    case(S_START):
        evnt = TAGinitialise();
        break;


    case(S_INITIALISE):
        evnt = E_CONTINUE;
        break;


    case(S_CHECK_OPERATION_MODE):
        switch (currentOperatingMode){
        case(M_USER):
            evnt = E_USER;
            break;

        case(M_SERVICE):
            evnt = E_SERVICE;
            break;

        default:
            break;
        }
        break;


    case(S_CHECK_TIME_TO_PASS):
        if(timeToPass != 0){
            evnt = E_PASS_TIME;
            break;
        }else{
            evnt = E_DONT_PASS_TIME;
        }
        break;


    case(S_PASS_TIME):
        if(timeToPass >= 30){
            LTincreaseTime(30);
            timeToPass -= 30;
        } else {
            LTincreaseTime(timeToPass);
            timeToPass = 0;
        }
        TCchangeTemperature();
        WCchangeWaterLevel();
        evnt = E_TIME_PASSED;
        break;


    case(S_CHECK_LIGHT_STATE):
        evnt = LClightCheck();
        static bool lightToggled = false;
        if(evnt == E_LIGHT_TOGGLE && lightToggled){
            evnt = E_LIGHT_ERROR;
        }
        lightToggled = false;
        break;


    case(S_TOGGLE_LIGHT):
        evnt = LCtoggleLight();
        lightToggled = true;
        break;


    case(S_CHECK_HEATER_STATE):
        evnt = TCtemperatureCheck();
        static bool heaterToggled = false;
        if(evnt == E_HEATER_TOGGLE && heaterToggled){
            evnt = E_HEATER_ERROR;
        }
        heaterToggled = false;
        break;


    case(S_TOGGLE_HEATER):
        evnt = TCtoggleHeater();
        heaterToggled = true;
        break;


    case(S_CHECK_WATER_LEVEL):
        evnt = WCwateringCheck();
        static bool watered = false;
        if(evnt == E_WATER_PLANT && watered){
            evnt = E_WATERING_ERROR;
        }
        watered = false;
        break;


    case(S_WATER_PLANT):
        evnt = WCwaterPlant();
        watered = true;
        break;


    case(S_CHECK_MORE_TIME_TO_PASS):
        if(timeToPass != 0){
            evnt = E_TIME_TO_PASS;
        }else{
            evnt = E_NO_TIME_TO_PASS;
        }
        break;


    case(S_WAIT_FOR_USER_INPUT):
        userAction = KYBgetAction();

        switch(userAction){
        case A_HELP:
            evnt = E_HELP;
            break;

        case A_SERVICE:
            DSPsimulationSystemInfo("Service mode entered.", 10000);
            currentOperatingMode = M_SERVICE;
            evnt = E_SERVICE;
            break;

        case A_TIME:
            evnt = E_TIME;
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


    case(S_UPDATE_USER_SYSTEM_INFO):
        DSPclearScreen();
        evnt = DSPsystemInfo(0);
        break;


    case(S_PRINT_USER_HELP):
        evnt = DSPhelp(0);
        break;


    case(S_INCREASE_TIME):
        DSPshow("Enter the time in minutes to be passed like this 'xxx'.");
        while (1) {
            timeToPass= KYBgetint(1000);

            if(timeToPass >= 1000){
                DSPshow("Try again.");
            }else{
                break;
            }
        }
        evnt = E_INCREASE_TIME;
        break;


    case(S_WAIT_FOR_SERVICE_INPUT):
        userAction = KYBgetAction();

        switch(userAction){
        case A_WATER:
            evnt = E_WATER;
            break;

        case A_LIGHT:
            evnt = E_LIGHT;
            break;

        case A_HEATER:
            evnt = E_HEATER;
            break;

        case A_PUMP:
            evnt = E_PUMP;
            break;

        case A_CHANGE:
            evnt = E_CHANGE;
            break;

        case A_ADD:
            evnt = E_ADD;
            break;

        case A_USER:
            currentOperatingMode = M_USER;
            evnt = E_USER;
            DSPsimulationSystemInfo("User mode entered.", 10000);
            DSPclearScreen();
            DSPsystemInfo(0);
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


    case(S_SERVICE_TOGGLE_PUMP):
        evnt = WCtogglePump();
        break;


    case(S_SERVICE_WATER_PLANT):
        evnt = WCwaterPlant();
        break;


    case(S_SERVICE_TOGGLE_HEATER):
        evnt = TCtoggleHeater();
        break;


    case(S_SERVICE_TOGGLE_LIGHT):
        evnt = LCtoggleLight();
        break;


    case(S_PRINT_SERVICE_HELP):
        evnt = DSPhelp(1);
        break;


    case(S_UPDATE_SERVICE_SYSTEM_INFO):
        DSPclearScreen();
        evnt = DSPsystemInfo(1);
        break;


    case(S_ASK_FOR_NEW_ACTIVE_PLANT):
        DSPshow("Choose a plant by entering the number before the plant name.");

        totalPlants = FMgetAmountOfPlants();

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

            if(plantIndex > totalPlants || plantIndex < 0){
                DSPshow("Try again.");
            }else{
                break;
            }
        }

        FMsetActivePlant(plantIndex);
        PTchangePlant(FMgetPlant(plantIndex));

        evnt = E_CHANGE_ACTIVE_PLANT;
        break;


    case(S_ASK_NEW_PLANT_INFO):
        DSPshow("Please enter the name of the plant.");
        int numberBuffer;
        int counter = 0;
        strcpy(addPlant.name, KYBgetString());

        while (counter < PLANT_NAME_SIZE) {
            if(addPlant.name[counter] == '\n'){
                break;
            }
            counter++;
        }
        addPlant.name[counter] = '\0';

        DSPshow("Please enter the maximum temperature.");
        while (1) {
            numberBuffer = KYBgetint(PLANT_MAX_TEMP_MAX + 1);

            if(numberBuffer > PLANT_MAX_TEMP_MAX | numberBuffer < 0){
                DSPshow("Try again.");
            }else{
                break;
            }
        }
        addPlant.tempMax = numberBuffer;

        DSPshow("Please enter the minimum temperature.");
        while (1) {
            numberBuffer = KYBgetint(PLANT_MAX_TEMP_MIN + 1);

            if(numberBuffer > PLANT_MAX_TEMP_MIN | numberBuffer < 0 | numberBuffer > addPlant.tempMax){
                DSPshow("Try again.");
            }else{
                break;
            }
        }
        addPlant.tempMin = numberBuffer;

        DSPshow("Please enter the maximum water level.");
        while (1) {
            numberBuffer = KYBgetint(PLANT_MAX_WATER_LEVEL + 1);

            if(numberBuffer > PLANT_MAX_WATER_LEVEL || numberBuffer < 0){
                DSPshow("Try again.");
            }else{
                break;
            }
        }
        addPlant.waterLevelMax = numberBuffer;

        DSPshow("Please enter the light hours.");
        while (1) {
            numberBuffer = KYBgetint(PLANT_MAX_LIGHT_HOURS + 1);

            if(numberBuffer > PLANT_MAX_LIGHT_HOURS || numberBuffer < 0){
                DSPshow("Try again.");
            }else{
                break;
            }
        }
        addPlant.lightHours = numberBuffer;
        evnt = FMsaveNewPlant(addPlant);
        break;


    case(S_ERROR):
        strcat(errorMessage, " - Error state reached.");
        DSPshowSystemError(errorMessage);
        DSPshow("Press the enter key to reset the system.");
        KYBgetString();
        TAGinitialise();
        evnt = E_RESOLVE_ERROR;
        break;

    default:
        evnt = E_NO;
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

    char displayBuffer[DISPLAY_SIZE];
    char numberBuffer[10];


    switch(currentState){
    case(S_NO):
        strcpy(displayBuffer, "S_NO in eventHandler: ");
        itoa(event, numberBuffer, 10);
        strcat(displayBuffer, numberBuffer);
        DSPshowSystemError(displayBuffer);
        nextState = S_START;
        KYBgetString();
        break;


    case(S_START):
        nextState = S_INITIALISE;
        break;


    case(S_INITIALISE):
        nextState = S_CHECK_OPERATION_MODE;
        break;


    case(S_CHECK_OPERATION_MODE):
        switch(event){
        case(E_USER):
            nextState = S_CHECK_TIME_TO_PASS;
            break;

        case(E_SERVICE):
            nextState = S_WAIT_FOR_SERVICE_INPUT;
            break;

        default:
            break;
        }
        break;


    case(S_CHECK_TIME_TO_PASS):
        switch (event) {
        case(E_PASS_TIME):
            nextState = S_PASS_TIME;
            break;

        case(E_DONT_PASS_TIME):
            nextState = S_CHECK_LIGHT_STATE;
            break;

        default:
            break;
        }
        break;


    case(S_PASS_TIME):
        nextState = S_CHECK_LIGHT_STATE;
        break;

    case(S_CHECK_LIGHT_STATE):
        switch (event) {
        case(E_LIGHT_STATE_OK):
            nextState = S_CHECK_HEATER_STATE;
            break;

        case(E_LIGHT_TOGGLE):
            nextState = S_TOGGLE_LIGHT;
            break;

        case(E_LIGHT_ERROR):
            strcpy(errorMessage, "Light error");
            nextState = S_ERROR;
            break;

        default:
            break;
        }
        break;

    case(S_TOGGLE_LIGHT):
        nextState = S_CHECK_LIGHT_STATE;
        break;

    case(S_CHECK_HEATER_STATE):
        switch (event) {
        case(E_HEATER_TOGGLE):
            nextState = S_TOGGLE_HEATER;
            break;

        case(E_HEATER_STATE_OK):
            nextState = S_CHECK_WATER_LEVEL;
            break;

        case(E_HEATER_ERROR):
            strcpy(errorMessage, "Heater error");
            nextState = S_ERROR;
            break;

        default:
            break;
        }
        break;

    case(S_TOGGLE_HEATER):
        nextState = S_CHECK_HEATER_STATE;
        break;

    case(S_CHECK_WATER_LEVEL):
        switch (event) {
        case(E_WATER_PLANT):
            nextState = S_WATER_PLANT;
            break;

        case(E_PLANT_WATER_OK):
            nextState = S_CHECK_MORE_TIME_TO_PASS;
            break;

        case(E_WATERING_ERROR):
            nextState = S_ERROR;
            strcpy(errorMessage, "Watering error");
            break;

        default:
            break;
        }
        break;


    case(S_WATER_PLANT):
        nextState = S_CHECK_WATER_LEVEL;
        break;


    case(S_CHECK_MORE_TIME_TO_PASS):
        switch (event) {
        case(E_TIME_TO_PASS):
            nextState = S_CHECK_TIME_TO_PASS;
            break;

        case(E_NO_TIME_TO_PASS):
            nextState = S_WAIT_FOR_USER_INPUT;
            break;

        default:
            break;
        }
        break;

    case(S_WAIT_FOR_USER_INPUT):
        switch (event) {
        case(E_HELP):
            nextState = S_PRINT_USER_HELP;
            break;

        case(E_TIME):
            nextState = S_INCREASE_TIME;
            break;

        case(E_UPDATE):
            nextState = S_UPDATE_USER_SYSTEM_INFO;
            break;

        case(E_SERVICE):
            nextState = S_CHECK_OPERATION_MODE;
            break;

        case(E_NON_VALID_INPUT):
            nextState = currentState;
            break;

        default:
            nextState = currentState;
            break;
        }
        break;


    case(S_UPDATE_USER_SYSTEM_INFO):
        nextState = S_WAIT_FOR_USER_INPUT;
        break;

    case(S_PRINT_USER_HELP):
        nextState = S_WAIT_FOR_USER_INPUT;
        break;

    case(S_INCREASE_TIME):
        nextState = S_CHECK_TIME_TO_PASS;
        break;

    case(S_WAIT_FOR_SERVICE_INPUT):
        switch (event) {
        case(E_HELP):
            nextState = S_PRINT_SERVICE_HELP;
            break;

        case(E_HEATER):
            nextState = S_SERVICE_TOGGLE_HEATER;
            break;

        case(E_LIGHT):
            nextState = S_SERVICE_TOGGLE_LIGHT;
            break;

        case(E_PUMP):
            nextState = S_SERVICE_TOGGLE_PUMP;
            break;

        case(E_WATER):
            nextState = S_SERVICE_WATER_PLANT;
            break;

        case(E_ADD):
            nextState = S_ASK_NEW_PLANT_INFO;
            break;

        case(E_CHANGE):
            nextState = S_ASK_FOR_NEW_ACTIVE_PLANT;
            break;

        case(E_USER):
            nextState = S_CHECK_OPERATION_MODE;
            break;

        case(E_UPDATE):
            nextState = S_UPDATE_SERVICE_SYSTEM_INFO;
            break;

        case(E_NON_VALID_INPUT):
            nextState = currentState;
            break;

        default:
            break;
        }
        break;


    case(S_PRINT_SERVICE_HELP):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_SERVICE_TOGGLE_PUMP):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_SERVICE_TOGGLE_HEATER):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_SERVICE_TOGGLE_LIGHT):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_SERVICE_WATER_PLANT):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_ASK_FOR_NEW_ACTIVE_PLANT):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_UPDATE_SERVICE_SYSTEM_INFO):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_ASK_NEW_PLANT_INFO):
        nextState = S_WAIT_FOR_SERVICE_INPUT;
        break;


    case(S_ERROR):
        nextState = S_CHECK_OPERATION_MODE;
        break;


    default:
        break;
    }
    currentState = nextState;
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

    return E_START;
}
