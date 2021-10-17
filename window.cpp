// ========================================================================== //
// Depenencies

// STL
#include <iostream>
#include <exception>

// local
#include "SDL-globals.hpp"
#include "window.hpp"

// ========================================================================== //
// local macro

#define CHECK_INIT() {if (!initialized) {throw std::runtime_error("Window not initialized.");}}

// ========================================================================== //
// CTor, DTor

Window::Window(const char *title, int width, int height) {
    hwin = SDL_CreateWindow(title,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            width, height,
                            SDL_WINDOW_SHOWN);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    win_renderer = SDL_CreateRenderer(hwin, -1, render_flags);

    initialized = true;
}
// .......................................................................... //
Window::~Window() {
    SDL_DestroyRenderer(win_renderer);
    SDL_DestroyWindow(hwin);

    hwin         = nullptr;
    win_renderer = nullptr;
    initialized  = false;
}

// ========================================================================== //
// operators

Window & Window::operator=(Window && other) {
    /* move assignment nulls the PTRs in other such that its DTor doesn't cause harm */

    initialized  = other.initialized;
    hwin         = other.hwin;
    win_renderer = other.win_renderer;
    callback     = other.callback;
    idleFunc     = other.idleFunc;
    idleData     = other.idleData;

    other.hwin = nullptr;
    other.win_renderer = nullptr;

    return *this;
}

// ========================================================================== //
// getters

SDL_Renderer * Window::getRenderer() const {CHECK_INIT(); return win_renderer;}
// -------------------------------------------------------------------------- //
int Window::getWidth() const {return SDL_GetWindowSurface(hwin)->w;}
// .......................................................................... //
int Window::getHeight() const {return SDL_GetWindowSurface(hwin)->h;}
// .......................................................................... //
std::pair<int, int> Window::getDimension() const {
    int w, h;
    SDL_GetWindowSize(hwin, &w, &h);

    return std::make_pair(w, h);
}
// -------------------------------------------------------------------------- //

// ========================================================================== //
// place, hide and show

void Window::setPosition (const int x, const int y) {SDL_SetWindowPosition(hwin, x, y);}
// .......................................................................... //
void Window::setDimension(const int x, const int y) {SDL_SetWindowSize    (hwin, x, y);}
// .......................................................................... //

// ========================================================================== //
// draw

void Window::print(const char * text,
                   const int x, const int y,
                   int width, int height,
                   SDL_Color color,
                   TTF_Font * font
) {
    CHECK_INIT();
    if (!text) {return;}

    if ( !font ) {font = font_fixedSize;}

    SDL_Surface * surfaceMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * msg = SDL_CreateTextureFromSurface(win_renderer, surfaceMessage);

    if (width  == -1) {width = surfaceMessage->w;}
    if (height == -1) {height = surfaceMessage->h;}

    SDL_Rect msg_rect = {x, y, width, height};

    SDL_RenderCopy(win_renderer, msg, NULL, &msg_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(msg);
}

// ========================================================================== //
// interaction

void Window::setCallback(const std::function<bool (SDL_Event &)> & newCallback) {CHECK_INIT(); callback = newCallback;}
// .......................................................................... //
void Window::setIdleFunc(const std::function<void (void *)> & newIdleFunc) {CHECK_INIT(); idleFunc = newIdleFunc;}
// .......................................................................... //
void Window::setIdleData(void * newIdleData) {CHECK_INIT(); idleData = newIdleData;}

// -------------------------------------------------------------------------- //

void Window::mainloop(int fps, bool autoClear) {
    CHECK_INIT();

    bool close = false;
    bool hasCallback = callback ? true : false;

    SDL_Event event;

    while (!close) {
        while (SDL_PollEvent(&event)) {
            if (hasCallback)            {callback(event);}
            if (event.type == SDL_QUIT) {close = true;}
        }

        if (autoClear) {SDL_RenderClear(win_renderer);}
        if (idleFunc) {idleFunc(idleData);}
        SDL_RenderPresent(win_renderer);

        SDL_Delay(1000 / fps);
    }

}

