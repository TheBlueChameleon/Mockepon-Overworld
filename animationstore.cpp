// ========================================================================== //
// dependencies

// STL
#include <string>
using namespace std::string_literals;

// local
#include "animationstore.hpp"

// ========================================================================== //
// local macro

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)

// ========================================================================== //
// CTor / DTor

AnimationStore::AnimationStore(GfxStore & gfxStore) :
    gfxStore(gfxStore)
{}

// ========================================================================== //
// Getter


// ========================================================================== //
// Setter / Changer
