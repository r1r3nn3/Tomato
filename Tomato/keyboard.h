#ifndef KEYBOARD_H
#define KEYBOARD_H

//--------------------keyboard--------------------//

typedef enum{
    A_HELP,
    A_UPDATE,
    A_SERVICE,
    A_TIME,
    A_LIGHT,
    A_HEATER,
    A_PUMP,
    A_CHANGE,
    A_ADD,
    A_USER,
    A_NO
} actions_e;

void KYBinitialise(void);
char KYBgetchar(void);
char* KYBgetString(void);
int KYBgetint(int ifWrongValue);
actions_e KYBgetAction(void);

#define INPUT_BUFFER_SIZE 10

#endif // KEYBOARD_H
