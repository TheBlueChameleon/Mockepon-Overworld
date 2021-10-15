#ifndef SDLGLOBALS_HPP
#define SDLGLOBALS_HPP

// ========================================================================== //
// dependencies

// SDL
#include <SDL2/SDL_ttf.h>

// ========================================================================== //
// proc

void initGlobals();
void freeGlobals();

// ========================================================================== //
// fonts

extern TTF_Font * font_fixedSize;

#endif // SDLGLOBALS_HPP
