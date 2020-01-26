#ifndef KEYBOARD_H
#define KEYBOARD_H

//--------------------keyboard--------------------//

typedef enum{   /// Defines the action help used to display the help menu.
    A_HELP,     /// Defines the action update used to clear and print the system information.
    A_UPDATE,   /// Defines the action service used to enter service mode.
    A_SERVICE,  /// Defines the action time used to increase time.
    A_TIME,     /// Defines the action water used to manualy water the plant.
    A_WATER,    /// Defines the action light used to toggle the grow light.
    A_LIGHT,    /// Defines the action heater used to toggle the heater.
    A_HEATER,   /// Defines the action pump used to toggle the pump.
    A_PUMP,     /// Defines the action change used to change the current active plant.
    A_CHANGE,   /// Defines the action add used to add a new plant.
    A_ADD,      /// Defines the action used to enter user mode.
    A_USER,     /// Defines the action used as a error state.
    A_NO
} actions_e;

void KYBinitialise(void);
char KYBgetchar(void);
char* KYBgetString(void);
int KYBgetint(int ifWrongValue);
actions_e KYBgetAction(void);

#define INPUT_BUFFER_SIZE 10

#endif // KEYBOARD_H
