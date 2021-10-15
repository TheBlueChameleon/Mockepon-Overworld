#ifndef WINDOW_HPP
#define WINDOW_HPP

// ========================================================================== //
// Depenencies

// STL
#include <functional>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// ========================================================================== //
// Class

class Window {
private:
    int width = -1;
    int height = -1;

    SDL_Window * win = nullptr;
    SDL_Renderer * win_renderer = nullptr;

    std::function<bool (SDL_Event &)> callback;
        /* callback functions should return true if the received event should
         * trigger leaving the main loop. */

    std::function<void (void * data)> idleFunc;
    void * idleData = nullptr;

public:
    // ---------------------------------------------------------------------- //
    // CTor, DTor
    Window(const char * title, int width = 800, int height = 600);
    ~Window();

    // ---------------------------------------------------------------------- //
    // populate

    void print(const char * text,
               const int x, const int y,
               int width = -1, int height = -1,
               SDL_Color * color = nullptr,
               TTF_Font * font = nullptr);

    // ---------------------------------------------------------------------- //
    // interactions

    void setCallback(const std::function<bool (SDL_Event &)> & newCallback);
    void setIdleFunc(const std::function<void (void *)> & newIdleFunc);

    void mainloop(bool onlyCallback = false);
    void setIdleData(void * newIdleData);
};

#endif // WINDOW_HPP
