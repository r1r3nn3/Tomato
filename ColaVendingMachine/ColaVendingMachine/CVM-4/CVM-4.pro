TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c11

SOURCES += main.c \
    fsm.c \
    display.c \
    coinAcceptor.c \
    changeDispenser.c \
    colaDispenser.c \
    keyboard.c

HEADERS += \
    fsm.h \
    display.h \
    coinAcceptor.h \
    changeDispenser.h \
    events.h \
    colaDispenser.h \
    keyboard.h

