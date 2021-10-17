#ifndef WINDOW_HPP
#define WINDOW_HPP

// ========================================================================== //
// Depenencies

// STL
#include <functional>
#include <utility>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// local
#include "SDL-globals.hpp"

// ========================================================================== //
// Class

class Window {
private:
    bool initialized = false;

    SDL_Window * hwin = nullptr;
    SDL_Renderer * win_renderer = nullptr;

    std::function<bool (SDL_Event &)> callback;
        /* callback functions should return true if the received event should
         * trigger leaving the main loop. */

    std::function<void (void * data)> idleFunc;
    void * idleData = nullptr;

public:
    // ---------------------------------------------------------------------- //
    // CTor, DTor

    Window() = default;
    Window(const char * title, int width = 800, int height = 600);
    ~Window();

    // ---------------------------------------------------------------------- //
    // Operators

    Window & operator= (Window && other);       // move assignment

    // ---------------------------------------------------------------------- //
    // getters

    SDL_Renderer * getRenderer() const;

    int getWidth() const;
    int getHeight() const;
    std::pair<int, int> getDimension() const;

    // ---------------------------------------------------------------------- //
    // place, hide and show

    void setPosition (const int x, const int y);
    void setDimension(const int x, const int y);

    // ---------------------------------------------------------------------- //
    // draw

    void clear();

    void print(const char * text,
               const int x, const int y,
               int width = -1, int height = -1,
               SDL_Color color = color_white,
               TTF_Font * font = nullptr);

    void update();

    // ---------------------------------------------------------------------- //
    // interactions

    void setCallback(const std::function<bool (SDL_Event &)> & newCallback);

    void setIdleFunc(const std::function<void (void *)> & newIdleFunc);
    void setIdleData(void * newIdleData);

    void mainloop(int fps = 30, bool autoClear = false);

};

#endif // WINDOW_HPP
