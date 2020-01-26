/// @file file_manager.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @brief This file is used to read or write to files.

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "string.h"
#include "dirent.h"

#include "file_manager.h"
#include "time_manager.h"
#include "display.h"

static FILE * logFile;
static FILE * plantFile;
static FILE * activePlantFile;

static const char fileFolder[PATH_MAX] = "../Tomato/files/";
static const char logFolder[PATH_MAX] = "log/";
static const char plantFolder[PATH_MAX] = "plants/";
static const char plantFileName[PATH_MAX] = "plants.csv";
static const char activePlantFileName[PATH_MAX] = "activePlant.txt";

static char logFileLocation[PATH_MAX];
static char plantFileLocation[PATH_MAX];
static char activePlantFileLocation[PATH_MAX];

/// Initialises the file manager.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void FMinitialise(void){
    char buffer[10];
    char dateFormat[30];
    int numberBuffer;

    // set file location for plants file
    strcpy(plantFileLocation, fileFolder);
    strcat(plantFileLocation, plantFolder);
    strcat(plantFileLocation, plantFileName);

    // set file location for active plant file
    strcpy(activePlantFileLocation, fileFolder);
    strcat(activePlantFileLocation, plantFolder);
    strcat(activePlantFileLocation, activePlantFileName);

    // create file location for log files with the format: hhmm_DDMMYYYY_log.txt
    strcpy(logFileLocation, fileFolder);
    strcat(logFileLocation, logFolder);

    numberBuffer = LTgetHours();
    if(numberBuffer < 10){
        strcpy(dateFormat, "0");
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    } else {
        itoa(numberBuffer, buffer, 10);
        strcpy(dateFormat, buffer);
    }

    numberBuffer = LTgetMinutes();
    if(numberBuffer < 10){
        strcat(dateFormat, "0");
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    } else {
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    }

    strcat(dateFormat, "_");

    numberBuffer = LTgetMonthDays();
    if(numberBuffer < 10){
        strcat(dateFormat, "0");
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    } else {
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    }

    numberBuffer = LTgetMonths();
    if(numberBuffer < 10){
        strcat(dateFormat, "0");
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    } else {
        itoa(numberBuffer, buffer, 10);
        strcat(dateFormat, buffer);
    }

    itoa(LTgetYears(), buffer, 10);
    strcat(dateFormat, buffer);
    strcat(logFileLocation, dateFormat);
    strcat(logFileLocation, "_log.txt");

    logFile = fopen(logFileLocation, "w");
    fseek(logFile, 0, SEEK_END);
    fprintf(logFile, "Log file from: %s\n", dateFormat);
    fprintf(logFile, "Current active plant is: %s\n", FMgetPlantName(FMgetActivePlant()));
    fclose(logFile);

    DSPshow("Initialised: File manager");
}

/// This function is used to write to the file that stores the current active plant.
/// @param[in] index This index will be writen to the file.
void FMsetActivePlant(int index){
    activePlantFile = fopen(activePlantFileLocation, "w");
    fprintf(activePlantFile, "%i\n", index);
    fclose(activePlantFile);

    char buffer[DISPLAY_SIZE];

    strcpy(buffer, "Active plant changed to: ");
    strcat(buffer, FMgetPlantName(index));

    DSPsimulationSystemInfo(buffer, 10000);
}

/// This function is used to get the index saved in the file that stores the current active plant.
/// @return The index used to retreive the the plant information from plants.csv.
int FMgetActivePlant(void){
    int returnValue;
    int counter = 0;
    char buffer[10];

    activePlantFile = fopen(activePlantFileLocation, "r");
    fseek(activePlantFile, 0, SEEK_SET);
    while (1) {
        fgets(buffer, 100, activePlantFile);
        if(10 == counter){
            break;
        }
        counter++;
    }
    returnValue = atoi(buffer);

    fclose(activePlantFile);

    return returnValue;
}

/// Used to write a text to the log file.
/// @param[in] messageType Deffines the type of messages that will be logged, 1 = error, 2 = status.
/// @param[in] text A pointer to the text that will be logged.
void FMwriteToLog(int messageType,const char *text){
    logFile = fopen(logFileLocation, "r+");
    fseek(logFile, 0, SEEK_END);

    switch(messageType){
    case(1):
        fprintf(logFile, "ERROR: ");
        break;

    case(2):
        fprintf(logFile, "STATUS: ");
        break;

    default:
        fprintf(logFile, "UNKNOWN: ");
        break;
    }

    fprintf(logFile, "%s\n", text);
    fclose(logFile);
}

/// Used to get the struct plant_t from the plants.csv file.
/// @param[in] plantIndex The index used to find the correct plant in the plants.csv file.
plant_t FMgetPlant(unsigned int plantIndex){
    plant_t returnPlant;
    char buffer[100];
    int counter = 1;

    strcpy(returnPlant.name, "");
    returnPlant.tempMax = 0;
    returnPlant.tempMin = 0;
    returnPlant.lightHours = 0;
    returnPlant.waterLevelMax = 0;

    if(plantIndex > FMgetAmountOfPlants()){
        return returnPlant;
    }

    plantFile = fopen(plantFileLocation, "r");
    fseek(plantFile, 0, SEEK_SET);
    while(1){
        fgets(buffer, 100, plantFile);
        if(plantIndex == counter){
            break;
        }
        counter++;
    }
    fclose(plantFile);

    counter = 0;
    while(1){
        if(buffer[counter] == '\0'){
            break;
        }
        if(buffer[counter] == ';'){
            buffer[counter] = ' ';
        }
        counter++;
    }

    sscanf(buffer, "%s %i %i %i %i\n", returnPlant.name, &returnPlant.tempMax, &returnPlant.tempMin, &returnPlant.lightHours, &returnPlant.waterLevelMax);

    return returnPlant;
}

/// This function is used to get the amount of saved plants in plants.csv.
/// @return The amount of plant saved in plants.csv.
int FMgetAmountOfPlants(void){
    int returnValue = 0;
    char buffer[100];
    char prevBuffer[100];

    plantFile = fopen(plantFileLocation, "r");
    fseek(plantFile, 0, SEEK_SET);

    while(1){
        fgets(buffer, 100, plantFile);
        if(!strcmp(buffer, prevBuffer)){
            break;
        } else {
            returnValue++;
        }

        strcpy(prevBuffer, buffer);
    }
    fclose(plantFile);

    return  returnValue;
}

/// This function is used to get the amount of saved plants in plants.csv.
/// @param[in] FMgetPlantName The index used to get the correct plant from plats.csv.
/// @return A pointer to a string containing the name of the plant using the #plantIndex.
const char * FMgetPlantName(int plantIndex){
    static plant_t plant;
    plant = FMgetPlant(plantIndex);

    return plant.name;
}

/// Used to save a plant to the plants.csv file.
/// @param[in] newPlant A struc containing the information that will be saved in plants.csv.
/// @post A new plant will be saved in the plants.csv file.
void FMsaveNewPlant(plant_t newPlant){
    plantFile = fopen(plantFileLocation, "r+");
    fseek(plantFile, 0, SEEK_END);
    fprintf(plantFile, "%s;%i;%i;%i;%i\n", newPlant.name, newPlant.tempMax, newPlant.tempMin, newPlant.lightHours, newPlant.waterLevelMax);
    fclose(plantFile);

    char buffer[DISPLAY_SIZE];

    strcpy(buffer, "Plant is added: ");
    strcat(buffer, newPlant.name);

    DSPsimulationSystemInfo(buffer, 10000);
}
