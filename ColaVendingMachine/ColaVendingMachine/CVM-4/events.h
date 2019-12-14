#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
   E_NO,  /// Used for initialisation of an event variable.
   E_START,
   E_CONTINUE,
   E_10C,
   E_20C,
   E_NOT_ENOUGH,
   E_ENOUGH,
   E_CHANGE_DISPENSE,
   E_NO_CHANGE_DISPENSE
} event_e;

#endif
