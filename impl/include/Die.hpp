#ifndef DIE_HPP
#define DIE_HPP

#include <vector>
#include <random>
#include <SDL2/SDL.h>
#include "cJSON.h"

#include "Texture.hpp"

namespace SDLDie
{

enum Activity {
    NON_ACTIVE = 0,
    ACTIVE     = 1
};

class Die final
{
using texture_t    = SDLTexture::Texture;
using point_t      = SDLTexture::point_t;
using size_t       =         std::size_t;
using renderer_ptr =       SDL_Renderer*;

    Activity   activity_ = NON_ACTIVE;
    int                    value_ = 1;
    SDL_Rect                    rect_;
    std::vector<texture_t>  textures_;

    renderer_ptr renderer_ = nullptr;

public:
    Die() {}

    void loadmedia(cJSON * createinfo, renderer_ptr renderer);

    void set_pos(const point_t &new_pos);
    void draw();
    void handle_event(SDL_Event *event);

    void roll_die();
    int get_status() { return value_; }

    void set_pos(SDL_Point pos);
    SDL_Point get_pos() { return SDL_Point{rect_.x, rect_.y}; }

    void be_active()    { activity_ =     ACTIVE;}
    void be_nonactive() { activity_ = NON_ACTIVE;}

    bool is_active()    { return activity_ ==     ACTIVE;}
    bool is_nonactive() { return activity_ == NON_ACTIVE;}

};

}

#endif
