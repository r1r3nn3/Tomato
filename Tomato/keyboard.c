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

/* Must match with enum actions_e */
const char actions [NUMBER_OF_ACTIONS][BUFFER_SIZE] = {
    "help",
    "update",
    "service",
    "time",
    "light",
    "heater",
    "pump",
    "change",
    "add",
    "user"
};

void KYBinitialise(void){
    DSPshow("Initialised: Keyboard");
}

char * KYBgetString(void){
    static char buffer[BUFFER_SIZE];
    unsigned int i = 0;

    while(1){
        buffer[i] = getchar();
        if(buffer[i] == '\n'){
            break;
        }
        i++;
    }
    buffer[i+1] = '\0';
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
actions_e KYBgetAction(void){
    actions_e returnValue;

    char buffer[BUFFER_SIZE];
    bool validAction = false;
    int i = 0;
    char *userInput = KYBgetString();

    while (1) {
        buffer[i] = userInput[i];
        if(buffer[i] == '\n'){
            buffer[i] = '\0';
            break;
        }
        i++;
    }

    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = (char)(tolower(buffer[i]));
    }

    for(returnValue = 0; returnValue < NUMBER_OF_ACTIONS; returnValue++){
         if(!strcmp(buffer, actions[returnValue])){
            validAction = true;
            break;
        }
    }

    if(validAction){
        return returnValue;
    } else {
        return A_NO;
    }

}
