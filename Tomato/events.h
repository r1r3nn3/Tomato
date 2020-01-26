#ifndef EVENTS_H
#define EVENTS_H

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
} event_e;

#endif // EVENTS_H
