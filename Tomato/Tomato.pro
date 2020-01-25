TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        display.c \
        file_manager.c \
        fsm.c \
        keyboard.c \
        light_control.c \
        main.c \
        plant_manager.c \
        temperature_control.c \
        time_manager.c \
        water_control.c

HEADERS += \
    display.h \
    events.h \
    file_manager.h \
    fsm.h \
    keyboard.h \
    light_control.h \
    plant_manager.h \
    time_manager.h \
    time_manager.h \
    temperature_control.h \
    water_control.h
