#include "string.h"
#include "stdio.h"
#include "display.h"
#include "stdbool.h"    // temp
#include "time.h"       // for time object TODO
#include "math.h"       // temp

// temp active greenhouse data
int tempWaterLevel = 70;
double tempTemperature = 26.5;
bool tempLight = true;
double tempTime = 12.50;    // also maybe use a actual time object?

// temp active plant data
char tempActivePlantType[10] = "Tomato";
int tempActiveMaxWaterLevel = 70;
double tempActiveMaxTemperature = 29;
double tempActiveMinTemperature = 22;
int tempActiveLightHours = 12;

char currentTime[6] = {"00:00"};

void calculateTime(double time){
    currentTime[0] = (char)((time/10)+48);
    currentTime[1] = (char)((int)time%10)+48;
    currentTime[2] = ':';
    time = fmod(time*100, 100)*0.6;
    currentTime[3] = (char)(time / 10 + 48);
    currentTime[4] = (char)(fmod(time, 10) + 48);
}

void DSPinitialise(void){
    printf("Initialised: Display");
}

void DSPsystemInfo(){
    // clear screen
    system("cls");

   // set text for light state
    static char lightOnOff[4];
    if (tempLight){
        strcpy(lightOnOff, "On");
    } else {
        strcpy(lightOnOff, "Off");
    }

    // set time in right format
    calculateTime(tempTime);

    // print the menu
    printf("\t\t\tTOMATO - THE AUTOMATIC GREENHOUSE \n\n");
    printf("Current values: \t\t\t Active plant \t\t %s \n", tempActivePlantType);
    printf("Water level \t %i %c \t\t\t Water level max \t %i %c \n", tempWaterLevel, '%', tempActiveMaxWaterLevel, '%');
    printf("Temperature \t %.1lf C \t\t Max temperature \t %.1lf C \n", tempTemperature, tempActiveMaxTemperature);
    printf("Light \t\t %s \t\t\t Min Temperature \t %.1lf C \n", lightOnOff, tempActiveMinTemperature);
    printf("Time \t\t %s \t\t\t Light hours \t\t %i \n", currentTime, tempActiveLightHours);
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
   printf("\n## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

void DSPdebugSystemInfo(const char *text)
{
    printf("\n## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

void DSPsimulationSystemInfo(const char *text)
{
    printf("\n## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

void DSPshowSystemError(const char *text)
{
    printf("\n## %-" DISPLAY_SIZE_STR "s ##\n", text);
}

