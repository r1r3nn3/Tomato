#ifndef KEYBOARD_H
#define KEYBOARD_H

//--------------------keyboard--------------------//
void KYBinitialise(void);
char KYBgetchar(void);
int KYBgetint(int ifWrongValue);

#define INPUT_BUFFER_SIZE 10

#endif // KEYBOARD_H
