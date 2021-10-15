TEMPLATE = app

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib
LIBS += -lSDL2
LIBS += -lSDL2_image
LIBS += -lSDL2_ttf

SOURCES += \
        SDL-globals.cpp \
        main.cpp \
        window.cpp

HEADERS += \
    SDL-globals.hpp \
    window.hpp
