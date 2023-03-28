#include <iostream>

#include "CustomException.hpp"
#include        "Mainloop.hpp"
#include          "Window.hpp"

namespace Backgammon 
{

bool Mainloop::init ()
{   
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        Custom_Exceptions::SDL_Init_Exception{SDL_GetError()};
        return false;
    }
    else 
    {
        //  Create window
        mWindow   = Window  {"Really Armenian Backgammon",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE};

        //  Create renderer
        mRenderer = Renderer{mWindow.get_window_ptr(),  FIRST_SUITABLE, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};
        mRenderer.set_renderer_draw_color(0xFF, 0xFF, 0xFF, 0xFF);

        //  Initialize PNG loading
        int png_flags = IMG_INIT_PNG;
        if (!(IMG_Init(png_flags) & png_flags))
        {
            Custom_Exceptions::IMG_Init_Exception{SDL_GetError()};
            return false;
        }

         //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            Custom_Exceptions::Mix_OpenAudio_Exception{SDL_GetError()};
            return false;
        }
    }

    return true;
}

void Mainloop::close()
{
    //  Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void run_backgammon()
{
    Mainloop mainloop {};

    if (mainloop.init() == false)
        std::cout << "Can't initialize a Mainloop object\n";
    else
    {
        bool quit = false;

        SDL_Event event;

        for (; !quit;)
        {
            for (; SDL_PollEvent(&event) != 0 ;)
            {
                //User requests quit
                if( event.type == SDL_QUIT )
                    quit = true;

            }

            //  Clear screen
            mainloop.clear_renderer();

            //  Update screen
            mainloop.present_renderer();
        }
    }

    mainloop.close();
}

}
