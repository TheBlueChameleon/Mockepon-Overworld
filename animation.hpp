#ifndef ANIMATION_HPP
#define ANIMATION_HPP

// ========================================================================== //
// Depenencies

// STL
#include <vector>

// SDL
#include <SDL2/SDL.h>

// local
#include "SDL-globals.hpp"
#include "gfxstore.hpp"

// ========================================================================== //
// Class

class Animation {
private:
    GfxStore & store;

    std::vector<int> frames;
    int currentFrame = 0;

public:
    Animation(GfxStore & store);
};

#endif // ANIMATION_HPP
