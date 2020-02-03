#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
    /// This event should never be used.
    E_NO,
    /// This event is used at the start of the program.
    E_START,
    /// This event is used to continue after initialisation.
    E_CONTINUE,
    /// This event is used when to make sure the user mode is used.
    E_USER,
    /// This event is used to pass time.
    E_PASS_TIME,
    /// This event is used to not pass time.
    E_DONT_PASS_TIME,
    /// This event is used when time is passed.
    E_TIME_PASSED,
    /// This event is used to toggle the grow light.
    E_LIGHT_TOGGLE,
    /// This event is used when the light is toggled.
    E_LIGHT_TOGGLED,
    /// This event is used when there is a error in the light subsystem.
    E_LIGHT_ERROR,
    /// This event is used when the light state is correct.
    E_LIGHT_STATE_OK,
    /// This event is used to toggle the heater.
    E_HEATER_TOGGLE,
    /// This event is used when the heater is toggled.
    E_HEATER_TOGGLED,
    /// This event is used when there is a error in the temperature subsystem.
    E_HEATER_ERROR,
    /// This event is used when the heater state is correct.
    E_HEATER_STATE_OK,
    /// This event is used to water the plant.
    E_WATER_PLANT,
    /// This event is used when the plant has been watered.
    E_WATERED_PLANT,
    /// This event is used when there is a error in the watering subsystem.
    E_WATERING_ERROR,
    /// This event is used when the water level in correct.
    E_PLANT_WATER_OK,
    /// This event is used to resolve software errors and resolved by initialising the system.
    E_RESOLVE_ERROR,
    /// This event is used when there is time to pass after checking the subsystems.
    E_TIME_TO_PASS,
    /// This event is used when there is no time to pass after checking the subsystems.
    E_NO_TIME_TO_PASS,
    /// This event is used when the operator entered a non valid input.
    E_NON_VALID_INPUT,
    /// This event is used to print the help menu.
    E_HELP,
    /// This event is used when the help menu is printed.
    E_HELP_PRINTED,
    /// This event is used to let the user increase time.
    E_TIME,
    /// This event is used to let time pass and check the subsystems.
    E_INCREASE_TIME,
    /// This event is used to update system information.
    E_UPDATE,
    /// This event is used when the system information is updated.
    E_SYSTEM_INFO_UPDATED,
    /// This event is used to enter service mode.
    E_SERVICE,
    /// This event is used to add a new plant.
    E_ADD,
    /// This event is used when a new plant is saved.
    E_NEW_PLANT_SAVED,
    /// This event is used to change the active plant.
    E_CHANGE,
    /// This event is used when the active plant is changed.
    E_CHANGE_ACTIVE_PLANT,
    /// This event is used to toggle the heater when in service mode.
    E_HEATER,
    /// This event is used to toggle the pump when in service mode.
    E_PUMP,
    /// This event is used when the pump is toggled.
    E_PUMP_TOGGLED,
    /// This event is used when there is a error in the watering subsystem.
    E_PUMP_ERROR,
    /// This event is used to toggle the light in service mode.
    E_LIGHT,
    /// This event is used to water the plant when in service mode.
    E_WATER
} event_e;


#endif // EVENTS_H
