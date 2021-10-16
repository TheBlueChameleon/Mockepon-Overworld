// ========================================================================== //
// dependencies

// STL
#include <cstdlib>
#include <iostream>

// SDL

// local
#include "SDL-globals.hpp"

// ========================================================================== //
// proc

void initAll () {
    if ( SDL_Init(SDL_INIT_EVERYTHING) ) {
        std::cerr << "error initializing SDL: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    } else {
        std::atexit(SDL_Quit);
    }

    if (TTF_Init() ) {
        std::cerr << "error initializing SDL: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    } else {
        std::atexit(TTF_Quit);
    }

    initGlobals();
}
// -------------------------------------------------------------------------- //
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
