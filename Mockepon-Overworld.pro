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
        animation.cpp \
        gfxstore.cpp \
        main.cpp \
        pugixml.cpp \
        window.cpp \
        xmlconvenience.cpp

HEADERS += \
    SDL-globals.hpp \
    animation.hpp \
    gfxstore.hpp \
    pugiconfig.hpp \
    pugixml.hpp \
    window.hpp \
    xmlconvenience.hpp
