#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"

namespace Custom_Exceptions
{
    struct IMG_Load_Exception : public Print_Exception
    {
        IMG_Load_Exception(const std::string& error_msg) :
            Print_Exception("Failure of loading img with error: " + error_msg) {}
    };

    struct SDL_CreateTextureFromSurface_Exception : public Print_Exception
    {
        SDL_CreateTextureFromSurface_Exception(const std::string& error_msg) :
            Print_Exception("Failure of initialization of SDL Library with error: " + error_msg) {}
    };

    struct SDL_RenderCopyEx : public Print_Exception
    {
        SDL_RenderCopyEx(const std::string& error_msg) :
            Print_Exception("Attempt to render unexisting texture: ") {}
    };

    struct SDL_DistructTexture_Exception : public Print_Exception {
        SDL_DistructTexture_Exception (const std::string& error_msg) :
            Print_Exception("Failure to distruct texture with error: " + error_msg) {}
    };
}

namespace SDLTexture
{

using renderer_ptr = SDL_Renderer*;
using texture_ptr  =  SDL_Texture*;
using texture_t    =   SDL_Texture;
using size_t       =   std::size_t;
using point_t      =     SDL_Point;



class Texture {

    private:
        texture_ptr texture_ = nullptr;
        point_t pos;
        size_t h = 0;                   
        size_t w = 0;                  
    
    public:
        Texture  (std::string& path, renderer_ptr renderer,
            int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
        ~Texture ();

        void move (point_t dst);
        void move (int delta_x, int delta_y);  

        void draw (int x, int y, size_t width, size_t height, 
            SDL_RendererFlip flip, renderer_ptr renderer);
        void drawframe(int x, int y, size_t width, size_t height, 
            int row, int frame, SDL_RendererFlip flip, renderer_ptr renderer);
};

}

#endif