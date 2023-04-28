#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <SDL2/SDL.h>

#include "CustomException.hpp"
#include "Transform.hpp"

#ifdef Ivan

namespace SDLGameObject
{

struct GameObjectInfo
{
using size_t = std::size_t;

    std::string       texture_id_;
    float     x_ = 0.0,  y_ = 0.0;
    size_t width_= 0, height_ = 0;
    SDL_RendererFlip        flip_;

    GameObjectInfo(const std::string& texture_id,   float x, float y, size_t width, size_t height,
                                                            SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        texture_id_ = texture_id;
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
        flip_ = flip;
    }
};

class GameObject
{
using size_t = std::size_t;
using transform_ptr = SDLTransform::Transform*;

    // transform_ptr       transform_;
    std::string        texture_id_;
    size_t width_ = 0, height_ = 0;
    SDL_RendererFlip         flip_;

public:
    GameObject(GameObjectInfo* createinfo) : 
    texture_id_{createinfo->texture_id_},
    width_{createinfo->width_}, height_{createinfo->height_},
    flip_{createinfo->flip_} 
    {
        // transform_ = new Transform(createinfo->x_, createinfo->y_);
    }

    virtual ~GameObject();

    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual void update(float dt) = 0;
    
};

}   //  end of the SDLGameObject namespace

#endif

#endif
