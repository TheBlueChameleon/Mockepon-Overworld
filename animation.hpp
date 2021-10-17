#ifndef ANIMATION_HPP
#define ANIMATION_HPP

// ========================================================================== //
// Depenencies

// STL
#include <vector>
#include <string>

// SDL
#include <SDL2/SDL.h>

// local
#include "SDL-globals.hpp"
#include "gfxstore.hpp"

// ========================================================================== //
// Class

class Animation {
private:
    GfxStore & gfxStore;

    std::vector<int> frames;
    unsigned int currentFrame = 0;

    std::pair<int, int> dimension = {-1, -1};

public:
    // ---------------------------------------------------------------------- //
    // CTor, DTor

    Animation(GfxStore & gfxStore);
    Animation(GfxStore & gfxStore, const std::string & filename);
    Animation(GfxStore & gfxStore, const std::vector<std::string> & filenames);

    // ---------------------------------------------------------------------- //
    // getters

    unsigned int getSize() const;

    const std::vector<int> & getFrames() const;

    unsigned int  getCurrentFrameID() const;
    SDL_Texture * getCurrentFrameTexture() const;

    // ---------------------------------------------------------------------- //
    // setters and changers

    void reset();

    void addFrame (int ID);
    void addFrame (const std::string & filename);

    void addFrames(const std::vector<int> & IDs);
    void addFrames(const std::vector<std::string> & filenames);

    void advanceFrame();

    // ---------------------------------------------------------------------- //
    // display

    void put (int x = 0, int y = 0);
    void show(int x = 0, int y = 0, int fps = 60);
    const std::vector<int> & getframes() const;
};

#endif // ANIMATION_HPP
