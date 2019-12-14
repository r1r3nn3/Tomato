TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c11

SOURCES += main.c \
    subsystems.c

HEADERS += \
    fsm.h \
    subsystems.h
