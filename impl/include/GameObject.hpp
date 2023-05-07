#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <SDL2/SDL.h>


#include <iostream>



#include "CustomException.hpp"
#include "Texture.hpp"

namespace SDLGameObject
{

enum Activity {
    ACTIVE     = 1,
    NON_ACTIVE = 0
};

using texture = SDLTexture::Texture;
using point_t = SDL_Point;


class GameObject
{
    texture   texture_;
    Activity activity_;

public:
    GameObject (const texture& rhs) : texture_(rhs), activity_(NON_ACTIVE) { }
    virtual ~GameObject() {} 

    GameObject (const GameObject& rhs) : texture_(rhs.texture_), activity_(rhs.activity_) { }

    void set_texture_pos (point_t new_pos) {
        texture_.set_pos(new_pos);
    }

    void draw () {
        texture_.draw();
    }

    void dump () {
        texture_.simple_dump();
        std::cout << "Activity = " << activity_ << std::endl;
    }  
};

} 

#endif
