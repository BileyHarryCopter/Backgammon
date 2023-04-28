#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include <map>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "CustomException.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

namespace Custom_Exceptions
{
    struct SDL_Init_Exception : public Print_Exception
    {
        SDL_Init_Exception(const std::string& error_msg) :
            Print_Exception("Failure of initialization of SDL Library with error: " + error_msg) {}
    };

    struct IMG_Init_Exception : public Print_Exception
    {
        IMG_Init_Exception(const std::string& error_msg) :
            Print_Exception("Failure with initialization of SDL_image: " + error_msg) {}
    };

    struct Mix_OpenAudio_Exception : public Print_Exception
    {
        Mix_OpenAudio_Exception(const std::string& error_msg) :
            Print_Exception("Failure with initialization of SDL_mixer: " + error_msg) {}
    };
}

namespace SDLMainloop
{

struct SDL
{
    SDL() 
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
            Custom_Exceptions::SDL_Init_Exception{SDL_GetError()};
    }
    ~SDL() { SDL_Quit(); }
};

class Mainloop
{

using music_ptr = Mix_Music *;
using renderer_ptr = SDL_Renderer *;

music_ptr music_ = nullptr;

#ifdef FONTS_SUPPORT
    TTF_Font*            mFont     = nullptr;
#endif

    SDL                                             sdl_;
    Window                                       window_;
    Renderer                                   renderer_;
    std::map<std::string, SDLTexture::Texture> textures_;

public:

    Mainloop();

    ~Mainloop();

    //  Loads audio files and textures
    bool loadmedia();

    //  Clear and present renderer
    void clear_renderer()   { renderer_.render_clear(); }
    void present_renderer() { renderer_.render_present(); }
    renderer_ptr get_renderer() { return renderer_.get(); }

    void draw_texture(const std::string& id,int x, int y, size_t width, size_t height,
                                            SDL_RendererFlip flip, renderer_ptr renderer);
                                        

private:

    SDLTexture::Texture& get_texture(const std::string &id) { return textures_.at(id); }

}; //   end of Mainloop's class

//  Creates an object of mainloop and runs the game
void run_backgammon();

}

#endif

