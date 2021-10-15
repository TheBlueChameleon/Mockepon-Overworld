// ========================================================================== //
// dependencies

// STL
#include <cstdlib>

// SDL

// local
#include "SDL-globals.hpp"

// ========================================================================== //
// proc

void initGlobals() {
    font_fixedSize= TTF_OpenFont("../font/FreeMono.ttf", 15);

    std::atexit(freeGlobals);
}
// .......................................................................... //
void freeGlobals() {
    TTF_CloseFont(font_fixedSize);
}

// ========================================================================== //
// fonts

TTF_Font * font_fixedSize = nullptr;
