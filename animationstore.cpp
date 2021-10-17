// ========================================================================== //
// dependencies

// STL
#include <cstring>

#include <string>
using namespace std::string_literals;
#include <filesystem>
namespace fs = std::filesystem;

// XML
#include "pugixml.hpp"

// local
#include "animationstore.hpp"
#include "convenienceprocs.hpp"

// ========================================================================== //
// local macro

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)

#define CHECK_GFX_INDEX(ID) {if ( (ID < 0) || (ID >= this->getSize()) ) {throw std::out_of_range(THROWTEXT("  Invalid AnimationStore ID: "s + std::to_string(ID)));}}

#define CHECK_FILE_EXISTS(filename) {if (!fs::exists(filename)) {throw std::runtime_error(THROWTEXT("  file not found: '"s + filename + "'"));}}

// ========================================================================== //
// CTor / DTor

AnimationStore::AnimationStore(GfxStore & gfxStore) :
    gfxStore(gfxStore)
{}


// ========================================================================== //
// Getter

unsigned int AnimationStore::getSize() const {return filenames.size();}
// .......................................................................... //
int AnimationStore::getAnimationID(const std::string & filename) const {
    auto searchIterator = std::find( filenames.begin(), filenames.end(), filename );
    if (searchIterator != filenames.end() ) {
        return std::distance(filenames.begin(), searchIterator);
    }

    return -1;
}
// .......................................................................... //
Animation & AnimationStore::getAnimation(const unsigned int ID) {
    CHECK_GFX_INDEX(ID);
    return animations[ID];
}

// ========================================================================== //
// Setter / Changer

void AnimationStore::reset() {
    filenames.clear();
    animations.clear();
}
// .......................................................................... //
int AnimationStore::addAnimation(const std::string & filename) {
    auto ID = getAnimationID(filename);
    if (ID != -1) {return ID;}

    auto doc = XMLload(filename, "animation");
    auto root = doc.child("project");
    auto nodeAnimation = root.child("animation");

    // push filenames directly, so that references to other animations can be resolved without infinite circles
    filenames.push_back(filename);
    animations.push_back( Animation(gfxStore) );

    for (auto node = nodeAnimation.first_child(); node; node = node.next_sibling()) {
        auto tag = node.name();

        if ( !std::strcmp(tag, "frame") ) {
            auto currentFile  = node.attribute("file").value();
            auto const repeat = node.attribute("repeat").as_int(1);

            for (auto i = 0; i < repeat; ++i) {animations.back().addFrame(currentFile);}

        } else if ( !std::strcmp(tag, "animation") ) {
            std::cout << "### not yet implemented" << std::endl;

            //auto refID = addAnimation();

        }
    }

    return filenames.size() - 1;
}
// -------------------------------------------------------------------------- //
void AnimationStore::advanceAll() {
    for (auto & ani : animations) {ani.advanceFrame();}
}
