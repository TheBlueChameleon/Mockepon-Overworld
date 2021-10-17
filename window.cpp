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

const char * Window::getTitle() {CHECK_INIT(); return SDL_GetWindowTitle(hwin);}
// -------------------------------------------------------------------------- //
int Window::getWidth () const {CHECK_INIT(); return SDL_GetWindowSurface(hwin)->w;}
// .......................................................................... //
int Window::getHeight() const {CHECK_INIT(); return SDL_GetWindowSurface(hwin)->h;}
// .......................................................................... //
std::pair<int, int> Window::getDimension() const {
    CHECK_INIT();

    int w, h;
    SDL_GetWindowSize(hwin, &w, &h);

    return std::make_pair(w, h);
}
// -------------------------------------------------------------------------- //
int Window::getPosX() const {CHECK_INIT(); return getPosition().first;}
// .......................................................................... //
int Window::getPosY() const {CHECK_INIT(); return getPosition().second;}
// .......................................................................... //
std::pair<int, int> Window::getPosition() const {
    CHECK_INIT();

    int x, y;
    SDL_GetWindowPosition(hwin, &x, &y);
    return std::make_pair(x, y);
}
// -------------------------------------------------------------------------- //
Uint32 Window::GetWindowFlags() const {CHECK_INIT(); return SDL_GetWindowFlags(hwin);}
// -------------------------------------------------------------------------- //
SDL_Renderer * Window::getRenderer() const {CHECK_INIT(); return win_renderer;}
// -------------------------------------------------------------------------- //

// ========================================================================== //
// place, hide and show

void Window::setTitle(const char * title) {CHECK_INIT(); SDL_SetWindowTitle(hwin, title);}
// -------------------------------------------------------------------------- //
void Window::setDimension(const int w, const int h) {CHECK_INIT(); SDL_SetWindowSize    (hwin, w, h);}
// .......................................................................... //
void Window::setPosition (const int x, const int y) {CHECK_INIT(); SDL_SetWindowPosition(hwin, x, y);}
// -------------------------------------------------------------------------- //
void Window::hide() {CHECK_INIT(); SDL_HideWindow(hwin);}
// .......................................................................... //
void Window::show() {CHECK_INIT(); SDL_ShowWindow(hwin);}
// -------------------------------------------------------------------------- //
void Window::minimize() {CHECK_INIT(); SDL_MinimizeWindow(hwin);}
// .......................................................................... //
void Window::maximize() {CHECK_INIT(); SDL_MaximizeWindow(hwin);}
// .......................................................................... //
void Window::restore() {CHECK_INIT(); SDL_RestoreWindow(hwin);}
// -------------------------------------------------------------------------- //
void Window::update() {CHECK_INIT(); SDL_RenderPresent(win_renderer);}

// ========================================================================== //
// drawing primitives

void Window::clear(bool autoUpdate) {
    CHECK_INIT();
    SDL_SetRenderDrawColor( win_renderer, 0, 0, 0, 255 );
                     SDL_RenderClear  (win_renderer);
    if (autoUpdate) {SDL_RenderPresent(win_renderer);}
}
// -------------------------------------------------------------------------- //
void Window::pset(int x, int y, SDL_Color color, bool autoUpdate) {
    SDL_SetRenderDrawColor( win_renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawPoint( win_renderer, x, y);
    if (autoUpdate) {SDL_RenderPresent(win_renderer);}
}
// .......................................................................... //
void Window::line(int x1, int y1, int x2, int y2, SDL_Color color, bool autoUpdate) {
    SDL_SetRenderDrawColor( win_renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawLine(win_renderer, x1, y1, x2, y2);
    if (autoUpdate) {SDL_RenderPresent(win_renderer);}
}
// .......................................................................... //
void Window::box(int x, int y, int w, int h, SDL_Color color, bool autoUpdate) {
    SDL_SetRenderDrawColor( win_renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(win_renderer, &rect);
    if (autoUpdate) {SDL_RenderPresent(win_renderer);}
}
// .......................................................................... //
void Window::fbox(int x, int y, int w, int h, SDL_Color color, bool autoUpdate) {
    SDL_SetRenderDrawColor( win_renderer, color.r, color.g, color.b, color.a );
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(win_renderer, &rect);
    if (autoUpdate) {SDL_RenderPresent(win_renderer);}
}
// -------------------------------------------------------------------------- //
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

void Window::mainloop(int fps, bool autoClear, bool onlyCallbackEvents) {
    CHECK_INIT();

    bool close = false;
    bool hasCallback = callback ? true : false;

    SDL_Event event;

    while (!close) {
        while (SDL_PollEvent(&event)) {
            if ( hasCallback)                                  {close = callback(event); break;}
            if (!onlyCallbackEvents && event.type == SDL_QUIT) {close = true;}
        }

        if (autoClear) {SDL_RenderClear(win_renderer);}
        if (idleFunc) {idleFunc(idleData);}

        SDL_RenderPresent(win_renderer);

        SDL_Delay(1000 / fps);
    }

}

