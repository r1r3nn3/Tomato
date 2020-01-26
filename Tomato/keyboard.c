/// @file keyboard.c
/// @author Alwin Rodewijk
/// @date 25-01-2020
/// @version V1.0
/// @brief This file is read input from the terminal window.

#include <stdio.h>
#include <ctype.h>
#include "stdbool.h"
#include "string.h"

#include "keyboard.h"
#include "display.h"

#define BUFFER_SIZE 30
#define NUMBER_OF_ACTIONS 11

/// @brief Used for comparing the user input.
/// The order of these strings must match the enum #actions_e.
const char actions [NUMBER_OF_ACTIONS][BUFFER_SIZE] = {
    "help",
    "update",
    "service",
    "time",
    "water",
    "light",
    "heater",
    "pump",
    "change",
    "add",
    "user"
};

/// Initialises the keyboard.
///
/// This is done at the start of this program.
/// @post This will show a text that the system is initialised.
void KYBinitialise(void){
    DSPshow("Initialised: Keyboard");
}

/// This function is used to read a string from the terminal window.
/// @return A pointer to a string containing the input from the user.
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

/// This function is used to read a character from the terminal window.
/// @return A character containing the input from the user.
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

/// This function is used to read a interger from the terminal window.
/// @param[in] ifWrongValue This value will be returned when the user entered a wrong value.
/// @return A interger containing the input from the user.
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

/// This function is used to read a action from the terminal window.
/// @return A action_e according to the user input.
actions_e KYBgetAction(void){
    actions_e returnValue;

    char buffer[BUFFER_SIZE];
    bool validAction = false;
    int counter = 0;

    strcpy(buffer, KYBgetString());

    while (1) {
        if(buffer[counter] == '\n'){
            buffer[counter] = '\0';
            break;
        }
        counter++;
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
