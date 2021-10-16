// ========================================================================== //
// dependencies

// STL
#include <string>
using namespace std::string_literals;

// local
#include "animation.hpp"

// ========================================================================== //
// local macro

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)

// ========================================================================== //
// local definitions

struct showIdleData {
    int x;
    int y;
    Animation * instance;
};

void showIdleFunc(void * data);

// ========================================================================== //
// CTor / DTor

Animation::Animation(GfxStore & store) :
    store(store)
{}
// .......................................................................... //
Animation::Animation(GfxStore & store, const std::string & xmlFile) :
    store(store)
{load(xmlFile);}


// ========================================================================== //
// Getter

unsigned int Animation::getSize() const {return frames.size();}
// .......................................................................... //
unsigned int Animation::getCurrentFrameID() const {return currentFrame;}
// .......................................................................... //
SDL_Texture * Animation::getCurrentFrameTexture() const {return store.getTexture(currentFrame);}

// ========================================================================== //
// Setter / Changer

void Animation::reset() {
    frames.clear();
    currentFrame = 0;
}
// .......................................................................... //
void Animation::addFrame(int ID) {
    if ( ID < 0 || ID >= store.getSize() ) {
        throw std::out_of_range(THROWTEXT("  Invalid GfxStore ID: "s + std::to_string(ID)));
    }

    if (dimension == std::make_pair(-1, -1)) {
        dimension = store.getImageDimensions(ID);
    } else {
        if (dimension != store.getImageDimensions(ID)) {
            throw std::runtime_error(THROWTEXT("  Invalid frame size!\n"
                                               "  Expected: "s +
                                               std::to_string(dimension.first) + "x" +
                                               std::to_string(dimension.second) + "\n"
                                               "  Found: " +
                                               std::to_string(store.getImageDimensions(ID).first) + "x" +
                                               std::to_string(store.getImageDimensions(ID).second) + "\n"
            ));
        }
    }

    frames.push_back( ID );
}
// .......................................................................... //
void Animation::addFrame(const std::string & filename) {
    addFrame( store.load(filename) );
}
// .......................................................................... //
void Animation::load(const std::string & xmlFile) {}
// .......................................................................... //
void Animation::advanceFrame() {
    ++currentFrame;
    currentFrame -= (currentFrame == frames.size()) * frames.size();
}

// ========================================================================== //
// display

void Animation::put(int x, int y) {
    SDL_Rect dest = {x, y, dimension.first, dimension.second};

    SDL_RenderCopy(store.getWin().getRenderer(),
                   store.getTexture(currentFrame),
                   NULL, &dest);
}
// .......................................................................... //
void Animation::show(int x, int y, int fps) {
    showIdleData data = {x, y, this};

    store.getWin().setIdleData(&data);
    store.getWin().setIdleFunc(showIdleFunc);

    store.getWin().mainloop(fps);
}
// .......................................................................... //
void showIdleFunc(void * data) {
    showIdleData * sData = static_cast<showIdleData *>(data);

    sData->instance->put(sData->x, sData->y);
    sData->instance->advanceFrame();
}
