#include "Texture.hpp"

#include <iostream>

namespace SDLTexture
{

Texture::Texture (const std::string& path, renderer_ptr renderer, int x, int y) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        Custom_Exceptions::IMG_Load_Exception{SDL_GetError()};
        std::cout << "Failure to load image! " << SDL_GetError() << std::endl;
    }

    else {
        texture_ = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if(texture_ == nullptr) {
            Custom_Exceptions::SDL_CreateTextureFromSurface_Exception{SDL_GetError()};
            std::cout << "Failure to create texture from surface! " << SDL_GetError() << std::endl;
        }

        else {
            SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h);
            pos_.x    = x;
            pos_.y    = y;
            path_     = path;
            renderer_ = renderer;
        }

        SDL_FreeSurface( loadedSurface );
    }
}

Texture::~Texture() {
    if(texture_ != nullptr)
        SDL_DestroyTexture(texture_);
    else
        Custom_Exceptions::SDL_DistructTexture_Exception{SDL_GetError()};
}

Texture::Texture (const Texture& rhs) {
    SDL_Surface* loadedSurface = IMG_Load(rhs.path_.c_str());

    if (loadedSurface == nullptr) {
        Custom_Exceptions::IMG_Load_Exception{SDL_GetError()};
        std::cout << "Failure to load image! " << SDL_GetError() << std::endl;
    }

    else {
        texture_ = SDL_CreateTextureFromSurface(rhs.renderer_, loadedSurface);

        if(texture_ == nullptr) {
            Custom_Exceptions::SDL_CreateTextureFromSurface_Exception{SDL_GetError()};
            std::cout << "Failure to create texture from surface! " << SDL_GetError() << std::endl;
        }

        else {
            SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h);
            pos_.x    = rhs.pos_.x;
            pos_.y    = rhs.pos_.y;
            path_     = rhs.path_;
            renderer_ = rhs.renderer_;
        }

        SDL_FreeSurface( loadedSurface );
    }
}

void Texture::simple_dump() {
    std::cout << "Texture addr = " << texture_ << "\n" 
              << "Pos = (" << pos_.x << ", " << pos_.y << ")\n" 
              << "H = " << h << ", W = " << w << "\n" 
              << std::endl;
}

void Texture::move (point_t dst) {
    pos_.x = dst.x;
    pos_.y = dst.y;
}

void Texture::move (int delta_x, int delta_y) {
    pos_.x += delta_x;
    pos_.y += delta_y;
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