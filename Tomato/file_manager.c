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
#include "dirent.h"

#include "file_manager.h"
#include "local_time.h"
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

void FMinitialise(void){
    char buffer[10];
    char dateFormat[30];
    int numberBuffer;

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
    fprintf(logFile, "Log file from: ");
    fprintf(logFile, "%s", dateFormat);
    fprintf(logFile, "\n");
    fclose(logFile);

    // set file location for plants file
    strcpy(plantFileLocation, fileFolder);
    strcat(plantFileLocation, plantFolder);
    strcat(plantFileLocation, plantFileName);

    // set file location for active plant file
    strcpy(activePlantFileLocation, fileFolder);
    strcat(activePlantFileLocation, plantFolder);
    strcat(activePlantFileLocation, activePlantFileName);

    DSPshow("Initialised: File manager");
}

void FMsetActivePlant(int index){
    activePlantFile = fopen(activePlantFileLocation, "w");
    putw(index, activePlantFile);
    fclose(activePlantFile);
}

int FMgetActivePlant(void){
    int returnValue;

    activePlantFile = fopen(activePlantFileLocation, "r");
    returnValue = getw(activePlantFile);
    fclose(activePlantFile);

    return returnValue;
}

//message types: 1 = error, 2 = status
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

    fprintf(logFile, "%s", text);
    fprintf(logFile, "\n");
    fclose(logFile);
}

// plant_t is empty index is wrong
plant_t FMgetPlant(int plantIndex){
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

const char * FMgetPlantName(int plantIndex){
    static plant_t plant;
    plant = FMgetPlant(plantIndex);

    return plant.name;
}

void FMsaveNewPlant(plant_t newPlant){
    plantFile = fopen(plantFileLocation, "r+");
    fseek(plantFile, 0, SEEK_END);
    fprintf(plantFile, "%s;%i;%i;%i;%i\n", newPlant.name, newPlant.tempMax, newPlant.tempMin, newPlant.lightHours, newPlant.waterLevelMax);
    fclose(plantFile);
}
