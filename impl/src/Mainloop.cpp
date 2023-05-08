#include <iostream>

#include "Mainloop.hpp"

namespace SDLMainloop
{
//----------
// Creation
//----------
Mainloop::Mainloop() :
    //  SDL initialization
    sdl_{},
    //  Create window
    window_{"Really Armenian Backgammon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE},
    //  Create renderer
    renderer_{window_,  FIRST_SUITABLE, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC}
    {
        //  Set color of background
        renderer_.set_renderer_draw_color(255, 255, 255, 255);

        //  Initialize PNG loading
        int png_flags = IMG_INIT_PNG;
        if (!(IMG_Init(png_flags) & png_flags))
            Custom_Exceptions::IMG_Init_Exception{SDL_GetError()};

        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            Custom_Exceptions::Mix_OpenAudio_Exception{SDL_GetError()};
    }

//------------
// Destruction
//------------
    Mainloop::~Mainloop()
    {
        //  Quit SDL subsystems
        Mix_Quit();
        IMG_Quit();
    }

    bool Mainloop::loadmedia()
    {
        menu_.loadmedia(renderer_.get());
        game_.loadmedia(renderer_.get());

        return true;
    }

    void Mainloop::update(bool *quit_status)
    {
        if (menu_.get_state() == SDLMenu::EXIT)
            *quit_status = true;
    }

//--------------
// Running loop
//--------------
    void run_backgammon()
    {
        Mainloop mainloop {};

        mainloop.loadmedia();

        bool quit = false;

        SDL_Event event;

        while (!quit)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                //User requests quit
                if( event.type == SDL_QUIT )
                    quit = true;
            }

            //  Clear screen
            mainloop.clear_renderer();

            mainloop.game_.draw();

            //  Update screen
            mainloop.present_renderer();
        }
    }
}
