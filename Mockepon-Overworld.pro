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
        animationstore.cpp \
        convenienceprocs.cpp \
        gfxstore.cpp \
        main.cpp \
        pugixml.cpp \
        window.cpp

HEADERS += \
    SDL-globals.hpp \
    animation.hpp \
    animationstore.hpp \
    convenienceprocs.hpp \
    gfxstore.hpp \
    pugiconfig.hpp \
    pugixml.hpp \
    window.hpp

DISTFILES += \
    unittest-xml/animation-pure.xml \
    unittest-xml/animation-ref.xml \
    unittest-xml/animation-sea.xml \
    unittest-xml/invalid-project-explicit.xml \
    unittest-xml/invalid-project-implicit.xml \
    unittest-xml/invalid-project-missing-name.xml \
    unittest-xml/invalid-version-major.xml \
    unittest-xml/invalid-version-minor.xml \
    unittest-xml/invalid-version-missing.xml \
    unittest-xml/invalid-version-text.xml \
    unittest-xml/tile-animation-direct.xml \
    unittest-xml/tile-animation-reference.xml \
    unittest-xml/valid-deprecated.xml
