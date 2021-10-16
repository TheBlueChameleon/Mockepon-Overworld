// ========================================================================== //
// Depenencies

// STL
#include <iostream>

// local
#include "SDL-globals.hpp"
#include "window.hpp"

// ========================================================================== //
// CTor, DTor

Window::Window(const char *title, int width, int height) {
    win_width  = width;
    win_height = height;

    win = SDL_CreateWindow(title,
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           width, height,
                           0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    win_renderer = SDL_CreateRenderer(win, -1, render_flags);
}
// .......................................................................... //
Window::~Window() {
    SDL_DestroyRenderer(win_renderer);
    SDL_DestroyWindow(win);
}

// ========================================================================== //
// getters

SDL_Renderer * Window::getRenderer() const {return win_renderer;}

// ========================================================================== //
// draw

void Window::print(const char * text,
                   const int x, const int y,
                   int width, int height,
                   SDL_Color color,
                   TTF_Font * font
) {
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

void Window::setIdleFunc(const std::function<void (void *)> & newIdleFunc) {idleFunc = newIdleFunc;}
// .......................................................................... //
void Window::setIdleData(void * newIdleData) {idleData = newIdleData;}
// .......................................................................... //
void Window::setCallback(const std::function<bool (SDL_Event &)> & newCallback) {callback = newCallback;}

// -------------------------------------------------------------------------- //

void Window::mainloop(bool autoClear, bool onlyCallback) {
    bool close = false;
    bool hasCallback = callback ? true : false;

    SDL_Event event;

    while (!close) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                if (!onlyCallback) {close = true;}
                else { if (hasCallback) {callback(event);} }
                break;

            default:
                if (hasCallback) {callback(event);}
                break;
            }
        }

        if (autoClear) {SDL_RenderClear(win_renderer);}
        if (idleFunc) {idleFunc(idleData);}
        SDL_RenderPresent(win_renderer);

        SDL_Delay(1000 / 30);
    }

}

