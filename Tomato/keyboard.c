/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           21-11-2019
*/

#include <stdio.h>
#include <ctype.h>
#include "stdbool.h"
#include "string.h"

#include "keyboard.h"
#include "display.h"

#define BUFFER_SIZE 30
#define NUMBER_OF_ACTIONS 10

/* Must match with enum e_actions */
const char actions [NUMBER_OF_ACTIONS][BUFFER_SIZE] = {
    "exit",
    "help",
    "update",
    "service",
    "time",
    "light",
    "heater",
    "pump",
    "change",
    "add"
};

void KYBinitialise(void){
    DSPshow("Initialised: Keyboard");
}

char * KYBgetString(void){
    static char buffer[BUFFER_SIZE];
    bool reading = true;
    unsigned int i = 0;

    while(reading){
        buffer[i] = getchar();
        if(buffer[i] == '\n'){
            reading = false;
        }
    }

    return buffer;
}

char KYBgetchar(void)
{
   char c = getchar();
   // First char read, empty input buffer
   while ((getchar()) != '\n')
   {
      // Remove all remaining buffered input chars
   }
   return c;
}

int KYBgetint(int ifWrongValue){
    int input = 0;
    int nOk = scanf(" %d", &input);
    // First int read, empty input buffer
    while ((getchar()) != '\n')
    {
       // Remove all remaining buffered input chars
    }
    // Check if input is an int (nOk == 1), if not return ifWrongValue
    if (nOk != 1) {
       input = ifWrongValue;
    }
    return input;
}


// Recomendation: use hash table or dictionary
e_actions KYBgetAction(void){
    e_actions returnValue = A_NO;

    bool gettingAction = true;

    while(gettingAction){
        char buffer[BUFFER_SIZE];

        strcpy(KYBgetString(), buffer);

        for(int i = 0; i < BUFFER_SIZE; i++){
            buffer[i] = (char)(tolower(buffer[i]));
        }

        int count = 0;

        for(; count < NUMBER_OF_ACTIONS; count++){
            if(strcmp(buffer, actions[count])){
                break;
                gettingAction = false;
            }
            if(count + 1 < NUMBER_OF_ACTIONS){
                DSPshow("Action not recognised try again.");
            }
        }

    }

    return returnValue;
}
