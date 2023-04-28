#include "Texture.hpp"

namespace SDLTexture
{

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

void Texture::move (point_t dst) {
    pos.x = dst.x;
    pos.y = dst.y;
}

void Texture::move (int delta_x, int delta_y) {
    pos.x += delta_x;
    pos.y += delta_y;
} 

void Texture::draw (int x, int y, size_t width, size_t height, 
                    SDL_RendererFlip flip, renderer_ptr renderer)
{
    if (mTexture == nullptr)
        Custom_Exceptions::SDL_RenderCopyEx{SDL_GetError()};

    SDL_Rect src_rect {0, 0, width, height};
    SDL_Rect dst_rect {x, y, width, height};

    SDL_RenderCopyEx(renderer, mTexture, &src_rect, &dst_rect, 0, nullptr, flip);
}

void Texture::drawframe(int x, int y, size_t width, size_t height, 
                        int row, int frame, SDL_RendererFlip flip, renderer_ptr renderer)
{
    if (mTexture == nullptr)
        Custom_Exceptions::SDL_RenderCopyEx{SDL_GetError()};

    SDL_Rect src_rect {width * frame, height * row, width, height};
    SDL_Rect dst_rect {x, y, width, height};

    SDL_RenderCopyEx(renderer, mTexture, &src_rect, &dst_rect, 0, nullptr, flip);
}

}