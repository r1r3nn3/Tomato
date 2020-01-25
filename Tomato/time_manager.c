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

static struct tm* local;
static time_t t;

static char timeBuffer[TIME_BUFFER_SIZE];

void setTimeToBuffer(){
    timeBuffer[2] = ':';
    // set hours
    if(local->tm_hour <= 9){
        timeBuffer[0] = '0';
        timeBuffer[1] = local->tm_hour + 48;
    } else {
        timeBuffer[0] = (local->tm_hour / 10) + 48;
        timeBuffer[1] = (local->tm_hour % 10) + 48;
    }
    // set minutes
    if(local->tm_min <= 9){
        timeBuffer[3] = '0';
        timeBuffer[4] = local->tm_min + 48;
    } else {
        timeBuffer[3] = (local->tm_min / 10) + 48;
        timeBuffer[4] = (local->tm_min % 10) + 48;
    }
}

void LTinitialise(void){
    t = time(NULL);
    local = localtime(&t);
    DSPshow("Initialised: Time manager");
}

const char* LTgetTime(char* output){
    setTimeToBuffer();
    strcpy(output, timeBuffer);
    return output;
}

int LTgetMinutes(void){
    return local->tm_min;
}

int LTgetHours(void){
    return local->tm_hour;
}

int LTgetYearDays(void){
    return local->tm_yday;
}

int LTgetMonthDays(void){
    return local->tm_mday;
}

int LTgetMonths(void){
    return local->tm_mon + 1;
}

int LTgetYears(void){
    return local->tm_year + 1900;
}

long int LTgetTimeObject(void){
    return t;
}

void LTincreaseTime(int minutes){
    t += minutes * 60;
    local = localtime(&t);
}





