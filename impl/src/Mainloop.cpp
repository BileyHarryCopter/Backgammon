#include <iostream>

#include "Mainloop.hpp"

namespace SDLMainloop
{

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
    SDLTexture::Texture board ("../../impl/assets/board_test.png", renderer_.get());

    SDLTexture::Texture bf_1_text ("../../impl/assets/black_feature.png", renderer_.get());

    SDLFeature::Feature bf_1 (bf_1_text, SDLFeature::BLACK);
 
    field_.push(bf_1);

    field_.move_feature(0, 1);

    textures_.insert({"board", board});

    

    return true;
}

void Mainloop::set_pos_texture(const std::string& id, int x, int y) {
    get_texture(id).set_pos({x, y});
}

void Mainloop::set_demension_texture (const std::string& id, int width, int height) {
    get_texture(id).set_demension(width, height);
}

void Mainloop::move_texture(const std::string& id, int delta_x, int delta_y) {
    get_texture(id).move(delta_x, delta_y);
}

void Mainloop::draw_texture(const std::string& id)
{
    get_texture(id).draw();
}

void Mainloop::draw_frame_texture(const std::string& id, int row, int frame) {
    get_texture(id).drawframe(row, frame);
}

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

        mainloop.draw_texture("board");
        mainloop.draw_field();

        //  Update screen
        mainloop.present_renderer();
    }

}

}
