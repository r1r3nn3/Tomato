#include "string.h"
#include "stdio.h"
#include "stdbool.h"
#include "time.h"
#include "math.h"

int tempWaterLevel = 70;
double tempTemperature = 26.5;
bool tempLight = true;
double tempTime = 12.50;    // because of convertion to int 0.xx1 is added, probebly because the actual value of 0.xx is smaller
                            // also maybe use a actual time object?

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
    double timeMinutes = fmod(time*100, 100)*0.6;
    currentTime[3] = (char)(timeMinutes / 10 + 48);
    currentTime[4] = (char)(fmod(timeMinutes, 10) + 48);
}

void DSPinitialise(void){
    printf("Display initialised");
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
    printf("-------------------------------------------------------------------------\n");

}

void DSPshow(const char *text){

}
void DSPdebugSystemInfo(const char *text){

}
void DSPsimulationSystemInfo(const char *text){

}
void DSPshowSystemError(const char *text){

}

