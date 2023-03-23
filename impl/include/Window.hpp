#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <utility>
#include <string>
#include <SDL2/SDL.h>

#include "CustomException.hpp"

namespace Backgammon
{

using namespace Custom_Exceptions;
namespace Custom_Exceptions
{

struct Create_Window_Exception : public Print_Exception
{
    Create_Window_Exception(const std::string& error_msg) :
            Print_Exception("Failure of creation the window with error: " + error_msg) {}
};

}

//  convenient constants for Window class:
constexpr std::size_t SCREEN_WIDTH = 1440;
constexpr std::size_t SCREEN_HEIGHT = 960;

class Window final
{

using window_ptr = SDL_Window*;
using window_t   = SDL_Window;
using size_t     = std::size_t;
using str_t      = std::string;

    window_ptr window_  = nullptr;
    size_t     width_   = SCREEN_WIDTH,           height_ = SCREEN_HEIGHT;
    int        posx_    = SDL_WINDOWPOS_CENTERED, posy_   = SDL_WINDOWPOS_CENTERED;
    str_t      title_   = "Backgammon";

public:

    Window () {}
    Window (const str_t& title, int posx, int posy, size_t width, size_t height, uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE):
            title_{title}, posx_{posx}, posy_{posy}, width_{width}, height_{height}
    {
        window_ = SDL_CreateWindow(title_.data(), posx_, posy_, width_, height_, flags);
        if (window_ == NULL)
            Create_Window_Exception("Error");
    }

    //  To avoid double SDL_DestroyWindow()
    Window(const Window &rhs) = delete;

    Window(Window&& rhs) noexcept : title_{ std::exchange(rhs.title_, 0)}, posx_{std::exchange(rhs.posx_, 0)}, posy_{std::exchange(rhs.posy_, 0)}, 
                                    width_{ std::exchange(rhs.width_, 0)}, height_{std::exchange(rhs.height_, 0)}, 
                                    window_{std::exchange(rhs.window_, nullptr)} {}

    Window& operator= (Window&& rhs)
    {
        std::swap(title_,  rhs.title_);
        std::swap(posx_,   rhs.posx_);
        std::swap(posy_,   rhs.posy_);
        std::swap(width_,  rhs.width_);
        std::swap(height_, rhs.height_);
        std::swap(window_, rhs.window_);

        return *this;
    }

    ~Window () 
    {
        if (window_ != NULL)
            SDL_DestroyWindow(window_);
    }

    //  Some method's accessors
    void set_posx(int posx)        { posx_   = posx; }
    void set_posy(int posy)        { posy_   = posy; }
    void set_width(size_t width)   { width_  = width; }
    void set_height(size_t height) { height_ = height; }

    //  Some selectors
    int get_posx()              { return posx_; }
    int get_posy()              { return posy_; }
    size_t get_width()          { return width_; }
    size_t get_height()         { return height_; }
    window_ptr get_window_ptr() { return window_; }

};  //  class Window

}

#endif
