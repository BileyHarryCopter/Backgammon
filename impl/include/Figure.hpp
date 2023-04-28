#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "GameObject.hpp"
#include "Texture.hpp"

#ifdef Ivan

namespace SDLFigure
{

class Figure final : public SDLGameObject::GameObject
{
using renderer_ptr   = SDL_Renderer*;
    int row_ = 0, frame_ = 0, framecount_ = 0;

public:

    void draw(const SDLTexture::Texture& texture, renderer_ptr renderer);
};

}

#endif

#endif
