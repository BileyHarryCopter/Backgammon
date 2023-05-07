#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "GameObject.hpp"

using texture = SDLTexture::Texture;

namespace SDLFeature
{

enum Colour {
    BLACK = 1,
    WHITE = 0
};

class Feature final : public SDLGameObject::GameObject
{
    Colour colour_;

public:
    Feature (texture& texture, Colour colour) : 
        GameObject(texture), colour_(colour) {}
    ~Feature () {}

    Feature (const Feature& rhs) : GameObject(rhs), colour_(rhs.colour_) {}

    void dump () {
        GameObject::dump();
        std::cout << "Colour = " << colour_ << std::endl;
    }
};

}

#endif
