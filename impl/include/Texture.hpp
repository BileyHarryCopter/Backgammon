#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"

namespace Backgammon
{

using renderer_ptr = SDL_Renderer*;
using texture_ptr  = SDL_Texture*;
using texture_t    = SDL_Texture;
using size_t       = std::size_t;
using point        = SDL_Point;

class Texture {

    private:
        texture_ptr mTexture = nullptr;
        point pos = {               
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED
        };  
        size_t h = 0;                   
        size_t w = 0;                  
    
    public:
        Texture  (std::string& path, size_t x, size_t y, renderer_ptr renderer);
        ~Texture ();

        void move (point dst);
        void move (int delta_x, int delta_y);   
};

Texture::Texture (std::string& path, size_t x = 0, size_t y = 0, renderer_ptr renderer) {

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    else {
        mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if(mTexture == nullptr) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        else {
            int w_cpy, h_cpy;
            SDL_QueryTexture(mTexture, nullptr, nullptr, &w_cpy, &h_cpy);

            if (w_cpy >= 0 && h_cpy >=0) {
                w = static_cast<size_t> (w_cpy);
                h = static_cast<size_t> (h_cpy);
            }

            else {
                std::cout << "Demensions of texture < 0! SDL Error: " << SDL_GetError() << std::endl;
            }

            if (x < 0 || x > SCREEN_WIDTH)
                std::cout << "Texture X position is out of bounds!" << std::endl;
            pos.x = x;

            if (y < 0 || y > SCREEN_HEIGHT)
                std::cout << "Texture Y position is out of bounds!" << std::endl;
            pos.y = y;
        }

        SDL_FreeSurface( loadedSurface );
    }
}

Texture::~Texture() {
    if(mTexture != nullptr)
        SDL_DestroyTexture(mTexture);
    else
        std::cout << "Unable to destroy texture! SDL Error: " << SDL_GetError() << std::endl;
}

}

#endif