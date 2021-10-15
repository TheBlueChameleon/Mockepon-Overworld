// ========================================================================== //
// Depenencies

// STL
#include <iostream>
#include <cstdlib>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// local
#include "SDL-globals.hpp"
#include "window.hpp"

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
void renderFunc ([[maybe_unused]] void * data) {
    Window * w = (Window *) data;
    w->print("stuff", 0, 0);
}

// ========================================================================== //
// main

int main() {
    initAll();

    Window w("stuff");

    w.setIdleFunc(renderFunc);
    w.setIdleData(&w);

    w.mainloop();

    return 0;
}
