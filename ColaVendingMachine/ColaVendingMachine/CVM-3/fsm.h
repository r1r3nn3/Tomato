#ifndef FSM_H
#define FSM_H

typedef enum {
   S_NO, // used for initialisation of a state variable
   S_START,
   S_INITIALISED,
   S_WAIT_FOR_COINS,
   S_DETECTED_10C,
   S_DETECTED_20C,
   S_DISPENSE,
   S_WAIT_FOR_UPDATE_CHANGE
} state_e;

typedef enum {
   E_NO, // used for initialisation of an event variable
   E_START,
   E_CONTINUE,
   E_10C,
   E_20C,
   E_NOT_ENOUGH,
   E_ENOUGH,
   E_CHANGE_DISPENSE, 
   E_NO_CHANGE_DISPENSE
} event_e;

#endif // FSM_H
