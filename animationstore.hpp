#ifndef ANIMATIONSTORE_HPP
#define ANIMATIONSTORE_HPP

// ========================================================================== //
// Depenencies

// STL
#include <iostream>
#include <exception>

#include <vector>
#include <string>
#include <utility>

// local
#include "gfxstore.hpp"
#include "animation.hpp"

// ========================================================================== //
// Class


class AnimationStore {
private:
    GfxStore & gfxStore;

    std::vector<std::string> filenames;
    std::vector<Animation>   animations;

public:
    // ---------------------------------------------------------------------- //
    // CTor, DTor

    AnimationStore(GfxStore & gfxStore);

    // ---------------------------------------------------------------------- //
    // getters

    unsigned int getSize() const;

    // ---------------------------------------------------------------------- //
    // setters and changers

    void reset();

    int addAnimation(const std::string & filename);

    void advanceAll();
};

#endif // ANIMATIONSTORE_HPP
