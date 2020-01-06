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


// temp active greenhouse data
static int tempWaterLevel = 70;
static double tempTemperature = 26.5;
static bool tempLight = true;

// temp active plant data
static char tempActivePlantType[10] = "Tomato";
static int tempActiveMaxWaterLevel = 70;
static double tempActiveMaxTemperature = 29;
static double tempActiveMinTemperature = 22;
static int tempActiveLightHours = 12;

void DSPinitialise(void){
    DSPshow("Initialised: Display");
}

void DSPsystemInfo(){
    // clear screen
    //system("cls");

   // set text for light state
    static char lightOnOff[4];
    if (tempLight){
        strcpy(lightOnOff, "On");
    } else {
        strcpy(lightOnOff, "Off");
    }

    // get time ready to print
    char timeBuffer[TIME_BUFFER_SIZE];
    LTgetTime(timeBuffer);

    // print the menu
    printf("\t\t\tTOMATO - THE AUTOMATIC GREENHOUSE \n\n");
    printf("Current values: \t\t\t Active plant \t\t %s \n", tempActivePlantType);
    printf("Water level \t %i %c \t\t\t Water level max \t %i %c \n", WCgetPlantWaterLevel(), '%', tempActiveMaxWaterLevel, '%');
    printf("Temperature \t %.1lf C \t\t Max temperature \t %.1lf C \n", tempTemperature, tempActiveMaxTemperature);
    printf("Light \t\t %s \t\t\t Min Temperature \t %.1lf C \n", lightOnOff, tempActiveMinTemperature);
    printf("Time \t\t %s \t\t\t Light hours \t\t %i \n", timeBuffer, tempActiveLightHours);
    DSPprintSeperator();
    printf("Enter 'help' followed by 'return' to show the available actions.\n");
    DSPprintSeperator();
    printf("\n");

}

void DSPhelp(){
    printf("\t--- Help menu ---\n");
    printf("You can use the following commands followed by 'return' to activate the actions:\n");
    printf("'clear' \t to clear the display from previous messages, this will not remove them from the log file\n");
    printf("'log' \t\t to open the current log file\n");
    printf("'service' \t to enter service mode\n");
    printf("'error' \t to check for errors manually, check will be performend in 'update'\n");
    printf("'update' \t followed by return, than '1-24' followed by return to update the time\n");
    printf("\n");
}

void DSPserviceInfo(){
    // system("cls");
    printf("\t--- Service menu ---\n");
    printf("'water' \t to toggle the watering system on/off \n");
    printf("'light' \t to toggle the liht on/off \n");
    printf("'heater' \t to toggle the heater on/off \n");
    printf("'select' \t to select a different active plant \n");
    printf("'add' \t\t to add a new plant type \n");
    printf("'back' \t\t to go back to the normal menu \n");
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
   printf("-- SIMULATION %-" DISPLAY_SIZE_STR "s\n", text);
}

void DSPshowSystemError(const char *text)
{
   printf("## SYSTEM ERROR %-" DISPLAY_SIZE_STR "s ##\n", text);
}

