#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utility>
#include <SDL2/SDL.h>

#include "CustomException.hpp"

namespace Backgammon
{

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
using renderer_t   = SDL_Renderer;
using window_ptr = SDL_Window*;
using window_t   = SDL_Window;

    renderer_ptr renderer_ = nullptr;

public:

    Renderer() {}

    Renderer(window_ptr window, int index, uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    {
        renderer_ = SDL_CreateRenderer(window, index, flags);
        if (renderer_ == NULL)
            Custom_Exceptions::Create_Render_Exception{SDL_GetError()};
    }

    //  To avoid double SDL_DestroyWindow()
    Renderer(const Renderer &rhs) = delete;

    Renderer(Renderer&& rhs) noexcept : renderer_{std::exchange(rhs.renderer_, nullptr)} {}

    Renderer& operator= (Renderer&& rhs)
    {
        std::swap(renderer_, rhs.renderer_);

        return *this;
    }

    ~Renderer () 
    {
        if (renderer_ != NULL)
            SDL_DestroyRenderer(renderer_);
    }

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

    void render_present ()  { SDL_RenderPresent(renderer_); }
};

}

#endif
