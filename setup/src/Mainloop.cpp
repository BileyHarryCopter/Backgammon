#include "../include/Mainloop.hpp"

namespace Backgammon {

bool Mainloop::init ()
{   
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Initialization of SDL video or audio with code of error: " << SDL_GetError() << std::endl;
        return false;
    }
    else 
    {
        //  Create window
        mWindow = SDL_CreateWindow("Backgammon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (mWindow == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			return false;
        }
        else
        {
            //  Create vsynced renderer for window
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                return false;
            }
            else 
            {
                //  Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return true;
}

void Mainloop::close()
{
    //Destroy window	
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
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
            SDL_SetRenderDrawColor(mainloop.get_renderer(), 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear(mainloop.get_renderer());

            //  Update screen
            SDL_RenderPresent(mainloop.get_renderer());
        }
    }

    mainloop.close();
}
}