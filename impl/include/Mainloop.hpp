#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "CustomException.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

namespace Backgammon
{

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

class Mainloop
{
    Mix_Music*           mMysic    = nullptr;
#ifdef FONTS_SUPPORT
    TTF_Font*            mFont     = nullptr;
#endif
    Window               mWindow;
    Renderer             mRenderer;
#ifdef TEXTURES_SUPPORT  
    std::vector<Texture> mTextures;
#endif

public:
    Mainloop() {}

    ~Mainloop() {}

    //  Initializes SDL and creates a window
    bool init();

    //  Loads audio files and images
    bool loadmedia();

    //  Cleans media and shuts down SDL
    void close();

    //  Clear and present renderer
    void clear_renderer()   { mRenderer.render_clear(); }
    void present_renderer() { mRenderer.render_present(); }

}; //   end of Mainloop's class

//  Creates an object of mainloop and runs the game
void run_backgammon();

}

#endif
