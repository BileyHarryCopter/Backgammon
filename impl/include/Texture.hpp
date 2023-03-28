#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>

#include "CustomException.hpp"

namespace Backgammon
{

struct Point 
{
    int x_= 0, y_= 0;
};

class Texture
{

using texture_ptr = SDL_Texture*;
using texture_t   = SDL_Texture;
using size_t      = std::size_t;

    texture_ptr texture_ = nullptr;
    size_t width_ = 0, height_ = 0;

public:

    Texture (){}
    ~Texture(){}

    void move (Point dst);

};
}

#endif
