// ========================================================================== //
// Depenencies

// STL
#include <string>
using namespace std::string_literals;
#include <filesystem>
namespace fs = std::filesystem;

#include <algorithm>

// local
#include "gfxstore.hpp"

// ========================================================================== //
// local macro

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)

#define CHECK_GFX_INDEX(ID) {if ( (ID < 0) || (ID >= this->getSize()) ) {throw std::out_of_range(THROWTEXT("  Invalid GfxStore ID: "s + std::to_string(ID)));}}

#define CHECK_FILE_EXISTS(filename) {if (!fs::exists(filename)) {throw std::runtime_error(THROWTEXT("  file not found: '"s + filename + "'"));}}

// ========================================================================== //
// CTor, DTor

GfxStore::GfxStore(Window & win) :
    win(win)
{}
// .......................................................................... //
GfxStore::~GfxStore() {
    reset();
}

// ========================================================================== //
// getters

Window & GfxStore::getWin() const {return win;}
// .......................................................................... //
int GfxStore::getSize() const {return textures.size();}
// -------------------------------------------------------------------------- //
const std::string & GfxStore::getFilename(const int ID) const {
    CHECK_GFX_INDEX(ID);
    return filenames[ID];
}
// .......................................................................... //
SDL_Texture * GfxStore::getTexture(const int ID) const {
    CHECK_GFX_INDEX(ID);
    return textures[ID];
}
// .......................................................................... //
std::pair<int, int> GfxStore::getImageDimensions(const int ID) const {
    CHECK_GFX_INDEX(ID);
    return dimensions[ID];
}

// ========================================================================== //
// setters and changers

void GfxStore::reset() {
    for (auto & tex : textures) {SDL_DestroyTexture(tex);}
}
// .......................................................................... //
int GfxStore::addFrame(const std::string & filename) {
    CHECK_FILE_EXISTS(filename);

    auto searchIterator = std::find( filenames.begin(), filenames.end(), filename );
    if (searchIterator != filenames.end() ) {
        return std::distance(filenames.begin(), searchIterator);
    }

    SDL_Surface* loadedSurface = IMG_Load( filename.c_str() );
    if( loadedSurface == NULL ) {
        throw std::runtime_error(THROWTEXT("Unable to load image " + filename + "!\n"
                                           "\tSDL_image Error: " + IMG_GetError()
        ));
    }

    SDL_Texture * newTexture = SDL_CreateTextureFromSurface( win.getRenderer(), loadedSurface );
    if( !newTexture ) {
        throw std::runtime_error(THROWTEXT("Unable to create texture from image " + filename + "!\n"
                                           "\tSDL_image Error: " + IMG_GetError()
        ));
    }

    filenames.push_back(filename);
    textures.push_back(newTexture);
    dimensions.push_back( std::make_pair(loadedSurface->w, loadedSurface->h) );

    SDL_FreeSurface( loadedSurface );

    return textures.size() - 1;
}

// ========================================================================== //
// display


void GfxStore::put(int ID, int x, int y) {
    CHECK_GFX_INDEX(ID);

    SDL_Rect dest = {x, y, dimensions[ID].first, dimensions[ID].second};

    SDL_RenderCopy(win.getRenderer(), textures[ID], NULL, &dest);
}
// .......................................................................... //
void GfxStore::show(int ID, int x, int y) {
    put(ID, x, y);
    win.mainloop();
}
// .......................................................................... //
