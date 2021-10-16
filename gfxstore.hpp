#ifndef GFXSTORE_HPP
#define GFXSTORE_HPP

// ========================================================================== //
// Depenencies

// STL
#include <iostream>
#include <exception>

#include <vector>
#include <string>
#include <utility>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// local
#include "SDL-globals.hpp"
#include "window.hpp"

// ========================================================================== //
// Class

class GfxStore {
private:
    std::vector<std::string  >       filenames;
    std::vector<SDL_Texture *>       textures;
    std::vector<std::pair<int, int>> dimensions;

    Window & win;

public:
    // ---------------------------------------------------------------------- //
    // CTor, DTor

    GfxStore(Window & win);
    ~GfxStore();

    // ---------------------------------------------------------------------- //
    // getters

          Window &      getWin() const;
    int                 getSize() const;
    const std::string & getFilename(const int ID) const;
          SDL_Texture * getTexture(const int ID) const;

    std::pair<int, int> getImageDimensions(const int ID);

    // ---------------------------------------------------------------------- //
    // setters and changers

    void reset();

    int addFrame (const std::string & filename);        // returns index of loaded image in store. Prevents double loading

    // ---------------------------------------------------------------------- //
    // display

    void put (int ID, int x = 0, int y = 0);
    void show(int ID, int x = 0, int y = 0);
};

#endif // GFXSTORE_HPP
