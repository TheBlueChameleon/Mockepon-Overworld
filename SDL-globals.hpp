#ifndef SDLGLOBALS_HPP
#define SDLGLOBALS_HPP

// ========================================================================== //
// dependencies

// SDL
#include <SDL2/SDL_ttf.h>

// ========================================================================== //
// proc

void initAll ();

void initGlobals();
void freeGlobals();

// ========================================================================== //
// colors

//extern SDL_Color color_white, color_black, color_red, color_green, color_blue, color_yellow, color_purple, color_cyan;
constexpr SDL_Color
    color_white  = {255, 255, 255,   0},
    color_black  = {  0,   0,   0,   0},
    color_red    = {255,   0,   0,   0},
    color_green  = {  0, 255,   0,   0},
    color_blue   = {  0,   0, 255,   0},
    color_yellow = {255, 255,   0,   0},
    color_purple = {255,   0, 255,   0},
    color_cyan   = {  0, 255, 255,   0};

// ========================================================================== //
// fonts

extern TTF_Font * font_fixedSize;

#endif // SDLGLOBALS_HPP
