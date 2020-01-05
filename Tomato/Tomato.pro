TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        display.c \
        fsm.c \
        keyboard.c \
        light_control.c \
        local_time.c \
        main.c \
        plant.c \
        service_control.c \
        temperature_control.c \
        water_control.c

HEADERS += \
    display.h \
    events.h \
    fsm.h \
    keyboard.h \
    light_control.h \
    local_time.h \
    plant.h \
    service_control.h \
    temperature_control.h \
    water_control.h
