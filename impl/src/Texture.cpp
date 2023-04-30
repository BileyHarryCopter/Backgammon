#include "Texture.hpp"

#include <iostream>

namespace SDLTexture
{

Texture::Texture (const std::string& path, renderer_ptr renderer, int x, int y) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        throw Custom_Exceptions::IMG_Load_Exception{SDL_GetError()};
    }

    else {

        texture_ = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if(texture_ == nullptr) {
            throw Custom_Exceptions::SDL_CreateTextureFromSurface_Exception{SDL_GetError()};
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
}

Texture::Texture (const Texture& rhs) {
    SDL_Surface* loadedSurface = IMG_Load(rhs.path_.c_str());

    if (loadedSurface == nullptr) {
        throw Custom_Exceptions::IMG_Load_Exception{SDL_GetError()};
    }

    else {
        texture_ = SDL_CreateTextureFromSurface(rhs.renderer_, loadedSurface);

        if(texture_ == nullptr) {
            throw Custom_Exceptions::SDL_CreateTextureFromSurface_Exception{SDL_GetError()};
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

void Texture::set_pos (point_t dst) {
    pos_.x = dst.x;
    pos_.y = dst.y;
}

void Texture::set_demension (int width, int height) {
    w = width;
    h = height;
}

void Texture::move (int delta_x, int delta_y) {
    pos_.x += delta_x;
    pos_.y += delta_y;
} 

void Texture::draw (SDL_RendererFlip flip)
{
    if (texture_ == nullptr)
        throw Custom_Exceptions::SDL_RenderCopyEx{SDL_GetError()};

    SDL_Rect src_rect {0, 0, w, h};
    SDL_Rect dst_rect {pos_.x, pos_.y, w, h};

    SDL_RenderCopyEx(renderer_, texture_, &src_rect, &dst_rect, 0, nullptr, flip);
}

void Texture::drawframe(int row, int frame, SDL_RendererFlip flip)
{
    if (texture_ == nullptr)
        throw Custom_Exceptions::SDL_RenderCopyEx{SDL_GetError()};

    SDL_Rect src_rect {w * frame, h * row, w, h};
    SDL_Rect dst_rect {pos_.x, pos_.y, w, h};

    SDL_RenderCopyEx(renderer_, texture_, &src_rect, &dst_rect, 0, nullptr, flip);
}

}