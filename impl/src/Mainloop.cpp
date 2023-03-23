#include <iostream>
#include "CustomException.hpp"
#include "Mainloop.hpp"
#include "Window.hpp"

namespace Backgammon 
{

using namespace Custom_Exceptions;

bool Mainloop::init ()
{   
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_Init_Exception{"Error"};
        return false;
    }
    else 
    {
        //  Create window
        mWindow = Window{"Really Armenian Backgammon",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE};

        mRenderer = Renderer{mWindow.get_window_ptr(),  FIRST_SUITABLE, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};
        mRenderer.set_renderer_draw_color(0xFF, 0xFF, 0xFF, 0xFF);
    }

    return true;
}

void Mainloop::close()
{
    //  Shut down SDL
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
