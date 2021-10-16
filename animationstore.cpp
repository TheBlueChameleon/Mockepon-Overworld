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

unsigned int AnimationStore::getSize() const {return filenames.size();}

// ========================================================================== //
// Setter / Changer

void AnimationStore::reset() {
    filenames.clear();
    animations.clear();
}
// .......................................................................... //
int AnimationStore::addAnimation(const std::string & filename) {
    auto searchIterator = std::find( filenames.begin(), filenames.end(), filename );
    if (searchIterator != filenames.end() ) {
        return std::distance(filenames.begin(), searchIterator);
    }

    std::vector<std::string> frameFiles;

    filenames.push_back(filename);
    animations.push_back( Animation(gfxStore, frameFiles) );

    return filenames.size() - 1;
}
// -------------------------------------------------------------------------- //
void AnimationStore::advanceAll() {
    for (auto & ani : animations) {ani.advanceFrame();}
}
