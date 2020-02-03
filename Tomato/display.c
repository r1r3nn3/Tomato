/// @file display.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is used to display text on the terminal window.

#include <stdio.h>
#include "stdbool.h"
#include "string.h"
#include "stdbool.h"
#include "time.h"

#include "display.h"
#include "plant_manager.h"
#include "time_manager.h"
#include "water_control.h"
#include "temperature_control.h"
#include "light_control.h"
#include "file_manager.h"

/// Initialises the display.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void DSPinitialise(void){
    DSPclearScreen();
    DSPshow("Initialised: Display");
}


/// Clears the terminal window.
void DSPclearScreen(void){
    system("cls");
}


/// Displays the system info.
/// @param[in] systemInfoType Used for displaying user (0) or service (1) info
/// @return A event that the system info has been updated.
event_e DSPsystemInfo(int systemInfoType){
    // get time ready to print
    char timeBuffer[TIME_BUFFER_SIZE];
    LTgetTime(timeBuffer);

    // print the menu
    printf("\t\t\tTOMATO - THE AUTOMATIC GREENHOUSE \n\n");
    printf("Current values: \t\t\t Active plant \t\t %s \n", PTgetName());
    printf("Water level \t %i %c \t\t\t Water level max \t %i %c \n", WCgetPlantWaterLevel(), '%', PTgetWaterLevelMax(), '%');
    printf("Temperature \t %.1lf C %s\t\t Max temperature \t %i C \n", TCgetCurrentTemperature(), (TCgetCurrentTemperature() < 10) ? "\t": "", PTgetTempMax());
    printf("Heater \t\t %s \t\t\t Min temperature \t %i C \n", TCgetHeaterState() ? "on" : "off", PTgetTempMin());
    printf("Light \t\t %s \t\t\t Light hours \t\t %i \n", LCgetState() ? "on" : "off", PTgetLightHours());
    switch (systemInfoType) {
    case 1:
        printf("Time \t\t %s \t\t\t Service mode\n", timeBuffer);
        break;

    case 0:
    default:
        printf("Time \t\t %s \t\t\t User mode\n", timeBuffer);
        break;
    }

    DSPprintSeperator();
    printf("Enter 'help' followed by the enter key to show the available actions.\n");
    DSPprintSeperator();
    printf("\n");

    return E_SYSTEM_INFO_UPDATED;
}


/// Displays the help menu.
/// @param[in] helpType Used for displaying the correct type of help menu, 0 = user, 1 = service.
/// @return A event that the help menu has been printed.
event_e DSPhelp(int helpType){
    switch(helpType){
    case(0):
        DSPprintSeperator();
        printf("\t--- User help menu ---\n");
        printf("Use the following commands followed by enter key:\n");
        printf("'help'\t\t to show this help menu.\n");
        printf("'update'\t to update the interface.\n");
        printf("'time'\t\t to increase the time.\n");
        printf("'service'\t to go to the service menu.\n");
        DSPprintSeperator();
        printf("\n");
        break;

    case(1):
        DSPprintSeperator();
        printf("\t--- Service help menu ---\n");
        printf("Use the following commands followed by enter key:\n");
        printf("'help'\t\t to show this help menu.\n");
        printf("'update'\t to update the interface.\n");
        printf("'water'\t\t to activate the watering system.\n");
        printf("'light'\t\t to toggle the light on/off.\n");
        printf("'heater'\t to toggle the heater on/off.\n");
        printf("'pump'\t\t to toggle the pump on/off.\n");
        printf("'add'\t\t to select a different active plant.\n");
        printf("'change'\t to change the current active plant.\n");
        printf("'user'\t\t to go to back to the user menu.\n");
        DSPprintSeperator();
        printf("\n");
        break;
    }

    return E_HELP_PRINTED;
}


/// Used in the display.c to display a seperator.
void DSPprintSeperator(){
    printf("-------------------------------------------------------------------------\n");
}


/// Used to display a string in a standaard format.
/// @param[in] text A pointer to the text that will be displayed.
void DSPshow(const char *text)
{
    printf("## %-" DISPLAY_SIZE_STR "s ##\n", text);
    printf("\n");
}


/// Used to display simulated system info.
/// @param[in] text A pointer to the text that will be displayed.
/// @param[in] valueForLog A interget value to be logged along side the text. If valueForLog > 10000 nothing will be displayed.
void DSPsimulationSystemInfo(const char *text, int valueForLog)
{
    char buffer[DISPLAY_SIZE + 10];
    char numberbuffer[10];

    LTgetTime(buffer);
    strcat(buffer, " - ");

    if(valueForLog < 10000){
        itoa(valueForLog, numberbuffer, 10);
        strcat(buffer, numberbuffer);
        strcat(buffer, " - ");
    }
    strcat(buffer, text);
    FMwriteToLog(2, buffer);

    LTgetTime(buffer);
    strcat(buffer, " - ");
    strcat(buffer, text);
    printf("-- SIMULATION %-" DISPLAY_SIZE_STR "s\n", buffer);
    printf("\n");
}


/// Used to display system errors.
/// @param[in] text A pointer to the text that will be displayed.
void DSPshowSystemError(const char *text)
{
    char buffer[DISPLAY_SIZE + 10];

    LTgetTime(buffer);
    strcat(buffer, " - ");
    strcat(buffer, text);

    FMwriteToLog(1, buffer);
    printf("!! SYSTEM ERROR %-" DISPLAY_SIZE_STR "s\n", text);
    printf("\n");
}
