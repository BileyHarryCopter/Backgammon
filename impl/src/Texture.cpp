#include "Texture.hpp"

namespace SDLTexture
{

Texture::~Texture() 
{
    if (texture_ != nullptr)
        SDL_DestroyTexture(texture_);
}

bool Texture::load(std::string filename, renderer_ptr renderer)
{
    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        Custom_Exceptions::IMG_Load_Exception{SDL_GetError()};
        return false;
    }

    if (texture_ != nullptr)
        drop();

    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture_ == nullptr)
    {
        Custom_Exceptions::SDL_CreateTextureFromSurface_Exception{SDL_GetError()};
        return false;
    }

    return true;
}

void Texture::drop()
{
    if (texture_ != nullptr)
        SDL_DestroyTexture(texture_);
}

void Texture::draw (int x, int y, size_t width, size_t height, 
                    SDL_RendererFlip flip, renderer_ptr renderer)
{
    if (texture_ == nullptr)
        Custom_Exceptions::SDL_RenderCopyEx{SDL_GetError()};

    SDL_Rect src_rect {0, 0, width, height};
    SDL_Rect dst_rect {x, y, width, height};

    SDL_RenderCopyEx(renderer, texture_, &src_rect, &dst_rect, 0, nullptr, flip);
}

void Texture::drawframe(int x, int y, size_t width, size_t height, 
                        int row, int frame, SDL_RendererFlip flip, renderer_ptr renderer)
{
    if (texture_ == nullptr)
        Custom_Exceptions::SDL_RenderCopyEx{SDL_GetError()};

    SDL_Rect src_rect {width * frame, height * row, width, height};
    SDL_Rect dst_rect {x, y, width, height};

    SDL_RenderCopyEx(renderer, texture_, &src_rect, &dst_rect, 0, nullptr, flip);
}

}