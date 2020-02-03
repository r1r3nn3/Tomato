#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
    E_NO,
    E_START,
    E_CONTINUE,
    E_USER,
    E_PASS_TIME,
    E_DONT_PASS_TIME,
    E_TIME_PASSED,
    E_LIGHT_TOGGLE,
    E_LIGHT_TOGGLED,
    E_LIGHT_ERROR,
    E_LIGHT_STATE_OK,
    E_HEATER_TOGGLE,
    E_HEATER_TOGGLED,
    E_HEATER_ERROR,
    E_HEATER_STATE_OK,
    E_WATER_PLANT,
    E_WATERED_PLANT,
    E_WATERING_ERROR,
    E_PLANT_WATER_OK,
    E_RESOLVE_ERROR,
    E_TIME_TO_PASS,
    E_NO_TIME_TO_PASS,
    E_NON_VALID_INPUT,
    E_HELP,
    E_HELP_PRINTED,
    E_TIME,
    E_INCREASE_TIME,
    E_UPDATE,
    E_SYSTEM_INFO_UPDATED,
    E_SERVICE,
    E_ADD,
    E_NEW_PLANT_SAVED,
    E_ADD_ERROR,
    E_CHANGE,
    E_CHANGE_ACTIVE_PLANT,
    E_CHANGE_ERROR,
    E_HEATER,
    E_PUMP,
    E_PUMP_TOGGLED,
    E_PUMP_ERROR,
    E_LIGHT,
    E_WATER,
    E_WATER_ERROR
} event_e;

/*
/// This enum is used for initialisation of an event variable
typedef enum {          /// This event represents a error.
    E_NO,               /// This event executes the start of the program.
    E_START,            /// This event executes the continuation of the program.
    E_CONTINUE,         /// This event executes the initialisation of the program.
    E_INIT_PLANT,       /// This event executes the increase of time.
    E_PASS_TIME,        /// This event executes the toggle of the grow lights.
    E_LIGHT_TOGGLE,     /// This event executes the toggle of the heater.
    E_HEATER_TOGGLE,    /// This event executes the watering of the currently active plant.
    E_WATER_PLANT,      /// This event asks the user for a action.
    E_ASK_USER_INPUT,   /// This event sets the increase of time.
    E_INCREASE_TIME,    /// This event represents a non valid input.
    E_NON_VALID_INPUT,  /// This event displays the help menu.
    E_HELP,             /// This event updates the system information.
    E_UPDATE,           /// This event sets the service mode on.
    E_SERVICE,          /// This event adds a new plant to the plant.csv file.
    E_ADD_PLANT,        /// This event changes the currently active plant to a selected plant from the plant.csv file.
    E_CHANGE_PLANT,     /// This event executes toggles the pump
    E_PUMP_TOGGLE,      /// This event set the service mode off.
    E_USER
} event_e;*/

#endif // EVENTS_H
