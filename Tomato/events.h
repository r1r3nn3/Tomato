#ifndef EVENTS_H
#define EVENTS_H

// used for initialisation of an event variable
typedef enum {
    E_NO,
    E_START,
    E_CONTINUE,
    E_INIT_PLANT,
    E_PASS_TIME,
    E_LIGHT_TOGGLE,
    E_HEATER_TOGGLE,
    E_WATER_PLANT,
    E_ASK_USER_INPUT,
    E_INCREASE_TIME,
    E_NON_VALID_INPUT,
    E_HELP,
    E_UPDATE,
    E_SERVICE,
    E_ADD_PLANT,
    E_CHANGE_PLANT,
    E_PUMP_TOGGLE,
    E_USER
} event_e;

#endif // EVENTS_H
