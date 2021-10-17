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

#define CHECK_GFX_INDEX(ID) {if ( (static_cast<int>(ID) < 0) || (ID >= this->getSize()) ) {throw std::out_of_range(THROWTEXT("  Invalid AnimationStore ID: "s + std::to_string(ID)));}}

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

    CHECK_FILE_EXISTS(filename);

    auto doc = XMLload(filename, "animation");
    auto root = doc.child("project");
    auto nodeAnimation = root.child("animation");

    // push filenames directly, so that references to other animations can be resolved without infinite circles
    auto myID = animations.size();
    filenames .push_back(filename);
    animations.push_back( Animation(gfxStore) );

    /* XML parsing
     * allow structures:
     * (1) Tag with attributes file, repeat
     * (2) Block with subtags frame, attributes file and repeat
     * (3) Block with subtags animation, attributes file and repeat
     *
     * Example:
     * <animation file="path/file1.xml" repeat="1">
     *  <frame file="path/file2.gfx" repeat="1">
     *  <reference file="path/file3.xml" repeat="1">
     * </animation>
     *
     * files are processed in the order they appear in the XML doc. That is, in the above example,
     * file1.xml is inserted as a first block; thereafter, file2.gfx is inserted; and finally,
     * file3.xml is inserted as a final block.
     *
     * The attribute repeat causes n-fold repetition of the insertion.
     */

    const auto currentFile = nodeAnimation.attribute("file").value();
    const auto repeat      = nodeAnimation.attribute("repeat").as_int(1);
    if (std::strlen(currentFile)) {
        auto refID = addAnimation(currentFile);
        for (auto i = 0; i < repeat; ++i) {animations[myID].addFrames( animations[refID].getFrames() );}
    }

    for (auto node = nodeAnimation.first_child(); node; node = node.next_sibling()) {
        auto tag = node.name();

        if ( !std::strcmp(tag, "frame") ) {
            const auto currentFile = node.attribute("file").value();
            const auto repeat      = node.attribute("repeat").as_int(1);

            for (auto i = 0; i < repeat; ++i) {animations[myID].addFrame(currentFile);}

        } else if ( !std::strcmp(tag, "animation") ) {
            std::cout << "### not yet implemented" << std::endl;

            const auto currentFile = node.attribute("file").value();
            const auto repeat      = node.attribute("repeat").as_int(1);

            if (std::strlen(currentFile)) {
                auto refID = addAnimation(currentFile);
                for (auto i = 0; i < repeat; ++i) {animations[myID].addFrames( animations[refID].getFrames() );}
            }

        }
    }

    return filenames.size() - 1;
}
// -------------------------------------------------------------------------- //
void AnimationStore::advanceAll() {
    for (auto & ani : animations) {ani.advanceFrame();}
}
