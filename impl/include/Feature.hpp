#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <SDL2/SDL.h>
#include <iostream>

#include "Texture.hpp"

namespace SDLFeature
{

enum Colour {
    BLACK = -1,
    NO_COLOR = 0,
    WHITE =  1
};

class Feature final
{
using texture_t = SDLTexture::Texture;
using point_t   = SDLTexture::point_t;

    Colour     colour_;
    texture_t texture_;

public:
    Feature(texture_t& texture, Colour colour) : colour_{colour}, texture_{texture} {}
    Feature (const Feature& rhs) : colour_{rhs.colour_}, texture_{rhs.texture_} {}
    
    ~Feature () {}

    void draw() { texture_.draw(); }
    void dump();

    Colour  get_colour()       { return colour_;}

    void set_texture_pos (point_t new_pos) { texture_.set_pos(new_pos); }
    int     get_texture_w()    { return texture_.get_w(); }
    int     get_texture_h()    { return texture_.get_h(); }
    point_t get_texture_pos()  { return texture_.get_pos(); }
};

}

#endif
