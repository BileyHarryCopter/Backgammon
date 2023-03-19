#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace Backgammon
{

//  Constants for mWindow
constexpr std::size_t SCREEN_WIDTH  = 640;
constexpr std::size_t SCREEN_HEIGHT = 480;

class Mainloop
{
    SDL_Window*   mWindow   = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    Mix_Music*    mMysic    = nullptr;
    TTF_Font*     mFont     = nullptr;

public:
    Mainloop() {}

    ~Mainloop() {}

    //  Initializes SDL and creates a window
    bool init();

    //  Loads audio files and images
    bool loadmedia();

    //  Cleans media and shuts down SDL
    void close();

//  Selectors:

    SDL_Renderer *get_renderer() const { return mRenderer; }
    SDL_Window     *get_window() const { return mWindow;}  

}; //   end of class Game

//  Creates an object of mainloop and runs the game
void run_backgammon();

}

#endif
