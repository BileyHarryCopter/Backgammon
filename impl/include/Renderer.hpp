#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <map>
#include <string>
#include <utility>
#include <SDL2/SDL.h>

#include "CustomException.hpp"
#include "Window.hpp"

namespace Custom_Exceptions
{
    struct Create_Render_Exception : public Print_Exception
    {
        Create_Render_Exception(const std::string &error_msg) : 
                Print_Exception("Failure with creation the renderer with error: " + error_msg) {}
    };

    struct Set_Render_DrawColor_Exception : public Print_Exception
    {
        Set_Render_DrawColor_Exception(const std::string &error_msg) : 
                       Print_Exception("Failure with setting a draw color for rendering with error: " + error_msg) {}
    };

    struct Render_Clear_Exception : public Print_Exception
    {
        Render_Clear_Exception(const std::string &error_msg) :
               Print_Exception("Failure with clear renderer with error: " + error_msg) {}
    };
}

constexpr int FIRST_SUITABLE = -1;

class Renderer final
{

using renderer_ptr = SDL_Renderer*;
using renderer_t   =  SDL_Renderer;
using texture_ptr  =  SDL_Texture*;
using texture_t    =   SDL_Texture;

    renderer_ptr                renderer_ = nullptr;
    Window                                 &window_;

public:

    Renderer(Window& window, int index, uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) :
            window_{window}
    {
        renderer_ = SDL_CreateRenderer(window_.get_window_ptr(), index, flags);
        if (renderer_ == NULL)
            Custom_Exceptions::Create_Render_Exception{SDL_GetError()};
    }

    Renderer(const Renderer &rhs) = delete;
    Renderer &operator=(const Renderer &rhs) = delete;

    Renderer(Renderer &&rhs) = delete;
    Renderer &operator=(Renderer &&rhs) = delete;

    ~Renderer () 
    {
        if (renderer_ != NULL)
            SDL_DestroyRenderer(renderer_);
    }

    renderer_ptr get() { return renderer_; }

    void set_renderer_draw_color (uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        if (SDL_SetRenderDrawColor (renderer_, red, green, blue, alpha) < 0)
            Custom_Exceptions::Set_Render_DrawColor_Exception{SDL_GetError()};
    }

    void render_clear ()
    {
        if (SDL_RenderClear(renderer_) < 0)
            Custom_Exceptions::Render_Clear_Exception{SDL_GetError()};
    }

    void render_present ()  
    {
        SDL_RenderPresent(renderer_);
    }
};

#endif
