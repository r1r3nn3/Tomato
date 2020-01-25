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
#include "time.h"

#include "display.h"
#include "plant_manager.h"
#include "time_manager.h"
#include "water_control.h"
#include "temperature_control.h"
#include "light_control.h"
#include "file_manager.h"


void DSPinitialise(void){
    DSPshow("Initialised: Display");
}

void DSPclearScreen(void){
    system("cls");
}

// systemInfoType = 0 for user menu
// systemInfoType = 1 for service menu
void DSPsystemInfo(int systemInfoType){
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
        printf("Time \t\t %s \t\t\t Service mode \t\t on\n", timeBuffer);
        break;

    case 0:
    default:
        printf("Time \t\t %s\n", timeBuffer);
        break;
    }

    DSPprintSeperator();
    printf("Enter 'help' followed by 'return' to show the available actions.\n");
    DSPprintSeperator();
    printf("\n");

}

// helpType = 0 for user menu
// helpType = 1 for service menu
void DSPhelp(int helpType){
    switch(helpType){
    case(0):
        DSPprintSeperator();
        printf("\t--- Help menu ---\n");
        printf("Use the following commands followed by 'enter':\n");
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
        printf("'help'\t\t to show this help menu.\n");
        printf("'update'\t to update the interface.\n");
        printf("'water'\t\t to activate the watering system.\n");
        printf("'light'\t\t to toggle the light on/off.\n");
        printf("'heater'\t to toggle the heater on/off.\n");
        printf("'pump'\t\t to toggle the pump on/off.\n");
        printf("'add'\t\t to select a different active plant.\n");
        printf("'change'\t to change the current active plant.\n");
        DSPprintSeperator();
        printf("\n");
        break;
    }


}

void DSPprintSeperator(){
    printf("-------------------------------------------------------------------------\n");
}

void DSPshow(const char *text)
{
    printf("## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

// to avoid logging a interget value, valueForLog > 10000
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
}

void DSPshowSystemError(const char *text)
{
    char buffer[DISPLAY_SIZE + 10];

    LTgetTime(buffer);
    strcat(buffer, " - ");
    strcat(buffer, text);

    FMwriteToLog(1, buffer);
    printf("## SYSTEM ERROR %-" DISPLAY_SIZE_STR "s ##\n", text);
}

