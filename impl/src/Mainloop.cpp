#include <iostream>

#include "Mainloop.hpp"

namespace SDLMainloop
{

Mainloop::Mainloop() :
    //  SDL initialization
    sdl_{},
    //  Create window
    window_{"Really Armenian Backgammon",   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE},
    //  Create renderer
    renderer_{window_,  FIRST_SUITABLE, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC}
{
    //  Set color of background
    renderer_.set_renderer_draw_color(0, 0, 0, 255);

    //  Initialize PNG loading
    int png_flags = IMG_INIT_PNG;
    if (!(IMG_Init(png_flags) & png_flags))
        Custom_Exceptions::IMG_Init_Exception{SDL_GetError()};

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        Custom_Exceptions::Mix_OpenAudio_Exception{SDL_GetError()};
}

Mainloop::~Mainloop()
{
    //  Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
}

bool Mainloop::loadmedia()
{
    SDLTexture::Texture texture{};

    texture.load("./assets/board_test.jpg", renderer_.get());

    textures_.insert({"board_test", texture});

    return true;
}

void Mainloop::draw_texture(const std::string& id,int x, int y, size_t width, size_t height,
                            SDL_RendererFlip flip, renderer_ptr renderer)
{
    get_texture(id).draw(x, y, width, height, flip, renderer);
}

void run_backgammon()
{
    Mainloop mainloop {};

    mainloop.loadmedia();

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

        mainloop.draw_texture("board_test", 100, 100, 200, 300, SDL_FLIP_NONE, mainloop.get_renderer());

        //  Update screen
        mainloop.present_renderer();
    }

}

}
