/*
Create by:      Alwin Rodewijk
Student nr:     635653
Class:          ENG-D-B1-ELTa
Subject:        D-B-INSE-O
Teacher:        Jos Onokiewicz
Date:           21-11-2019
*/

#include "stdio.h"
#include "stdbool.h"
#include "keyboard.h"
#include "display.h"
#include "string.h"

char buffer[INPUT_BUFFER_SIZE];

void KYBinitialise(void){
    DSPshow("Inintialised: keyboard");
}
char KYBgetchar(void){
    bool reading = true;
    int i = 0;
    char tempChar;

    strcpy(buffer, "\0\0\0\0\0\0\0\0\0\0");

    while(reading){
        tempChar = getchar();
        if(tempChar != '\n'){
            if (i >= 9){
                while ((getchar()) != '\n')
                {
                   // Remove all remaining buffered input chars
                }
                reading = false;
            } else{
                buffer[i] = tempChar;
                i++;
            }
        } else {
            reading = false;
        }
    }
    return buffer[0];
}
int KYBgetint(int ifWrongValue){


    return '0';
}
