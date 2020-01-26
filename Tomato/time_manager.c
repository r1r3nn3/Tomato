/// @file time_manager.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is used to manage the time.

#include <stdio.h>
#include "stdbool.h"
#include "string.h"
#include "stdbool.h"
#include "time.h"

#include "display.h"
#include "plant_manager.h"
#include "time_manager.h"

/// @brief Used to retreive the time information.
struct tm* local;
/// @brief Used to get the local time.
time_t t;

/// @brief Used to display the time in a standaard format.
char timeBuffer[TIME_BUFFER_SIZE];

/// Used inside this file to write the time from the tm object to #timeBuffer.
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

/// Initialises the time manager.
/// Sets the machine time to the current time.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void LTinitialise(void){
    t = time(NULL);
    local = localtime(&t);
    DSPshow("Initialised: Time manager");
}

/// This function is used to write to the file that stores the current active plant.
/// @param[in] output This pointer is used to write to a character array with the hours and minutes.
const char* LTgetTime(char* output){
    setTimeToBuffer();
    strcpy(output, timeBuffer);
    return output;
}

/// This function is used to get the minutes from the time object.
/// @return The amount of minutes in the time object #local.
int LTgetMinutes(void){
    return local->tm_min;
}

/// This function is used to get the hours from the time object.
/// @return The amount of hours in the time object #local.
int LTgetHours(void){
    return local->tm_hour;
}

/// This function is used to get the days of this year from the time object.
/// @return The amount of days of this year in the time object #local.
int LTgetYearDays(void){
    return local->tm_yday;
}

/// This function is used to get the month of this year from the time object.
/// @return The amount of days of this month in the time object #local.
int LTgetMonthDays(void){
    return local->tm_mday;
}

/// This function is used to get the months from the time object.
/// @return The amount of months in the time object #local.
int LTgetMonths(void){
    return local->tm_mon + 1;
}

/// This function is used to get the years from the time object.
/// @return The amount of years in the time object #local.
int LTgetYears(void){
    return local->tm_year + 1900;
}

/// This function is used to get the value of struct time_t #t.
/// @return struct time_t #t in the form of a long int.
long int LTgetTimeObject(void){
    return t;
}

/// This function is used to increase the time off the time object.
/// @param[in] minutes The amount off minutes the time will be increased.
void LTincreaseTime(int minutes){
    t += minutes * 60;
    local = localtime(&t);
}





