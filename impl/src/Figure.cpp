#include "Figure.hpp"

#ifdef Ivan

namespace SDLFigure
{
    
void Figure::draw(const SDLTexture::Texture& texture, renderer_ptr renderer)
{
    textures.draw(GameObject::texture_id_, GameObject::transform_->x_, GameObject::transform_->y_,
                  GameObject::width_, GameObject::height_, GameObject::flip_, renderer);
}

}

#endif
