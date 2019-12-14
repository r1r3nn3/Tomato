TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        display.c \
        events.c \
        fsm.c \
        keyboard.c \
        light_control.c \
        main.c \
        temperature_control.c \
        water_control.c

HEADERS += \
    display.h \
    events.h \
    fsm.h \
    keyboard.h \
    light_control.h \
    temperature_control.h \
    water_control.h
