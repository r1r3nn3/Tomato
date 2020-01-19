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
#include "plant.h"
#include "local_time.h"
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

void DSPsystemInfo(){
    // get time ready to print
    char timeBuffer[TIME_BUFFER_SIZE];
    LTgetTime(timeBuffer);

    // print the menu
    printf("\t\t\tTOMATO - THE AUTOMATIC GREENHOUSE \n\n");
    printf("Current values: \t\t\t Active plant \t\t %s \n", PTgetName());
    printf("Water level \t %i %c \t\t\t Water level max \t %i %c \n", WCgetPlantWaterLevel(), '%', PTgetWaterLevelMax(), '%');
    printf("Temperature \t %.1lf C \t\t Max temperature \t %i C \n", TCgetCurrentTemperature(), PTgetTempMax());
    printf("Light \t\t %s \t\t\t Min Temperature \t %i C \n", LCgetState() ? "on" : "off", PTgetTempMin());
    printf("Time \t\t %s \t\t\t Light hours \t\t %i \n", timeBuffer, PTgetLightHours());
    DSPprintSeperator();
    printf("Enter 'help' followed by 'return' to show the available actions.\n");
    DSPprintSeperator();
    printf("\n");

}

void DSPhelp(){
    DSPprintSeperator();
    printf("\t--- Help menu ---\n");
    printf("Use the following commands followed by 'enter':\n");
    printf("'help'\t\t to show this help menu.\n");
    printf("'update'\t to update the interface.\n");
    printf("'time'\t\t to increase the time.\n");
    printf("'service'\t to go to the service menu.\n");
    DSPprintSeperator();
    printf("\n");
}

void DSPserviceInfo(){
    DSPprintSeperator();
    printf("\t--- Service menu ---\n");
    printf("'user'\t\t to toggle the watering system on/off.\n");
    printf("'light'\t\t to toggle the light on/off.\n");
    printf("'heater'\t to toggle the heater on/off.\n");
    printf("'pump'\t\t to toggle the pump on/off.\n");
    printf("'add'\t\t to select a different active plant.\n");
    printf("'change'\t to change the current active plant.\n");
    DSPprintSeperator();
    printf("\n");
}

void DSPprintSeperator(){
    printf("-------------------------------------------------------------------------\n");
}

void DSPshow(const char *text)
{
    printf("## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

void DSPdebugSystemInfo(const char *text)
{
    printf("-- DEBUG %-" DISPLAY_SIZE_STR "s\n", text);
}

void DSPsimulationSystemInfo(const char *text)
{
    FMwriteToLog(2, text);
    printf("-- SIMULATION %-" DISPLAY_SIZE_STR "s\n", text);
}

void DSPshowSystemError(const char *text)
{
    FMwriteToLog(1, text);
    printf("## SYSTEM ERROR %-" DISPLAY_SIZE_STR "s ##\n", text);
}

