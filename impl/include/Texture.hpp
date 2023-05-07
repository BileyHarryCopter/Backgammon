#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Window.hpp"

using renderer_ptr = SDL_Renderer*;
using texture_ptr  =  SDL_Texture*;
using texture_t    =   SDL_Texture;
using point_t      =     SDL_Point;
using str_t        =   std::string;

namespace Custom_Exceptions
{
    struct IMG_Load_Exception : public Base_Exception {
        IMG_Load_Exception(const std::string& error_msg) :
            Base_Exception("Failure of loading img with error: " + error_msg) {}
    };

    struct SDL_CreateTextureFromSurface_Exception : public Base_Exception {
        SDL_CreateTextureFromSurface_Exception(const std::string& error_msg) :
            Base_Exception("Failure of initialization of SDL Library with error: " + error_msg) {}
    };

    struct SDL_RenderCopyEx : public Base_Exception {
        SDL_RenderCopyEx(const std::string& error_msg) :
            Base_Exception("Attempt to render unexisting texture: " + error_msg) {}
    };

    struct SDL_DistructTexture_Exception : public Base_Exception {
        SDL_DistructTexture_Exception (const std::string& error_msg) :
            Base_Exception("Failure to distruct texture with error: " + error_msg) {}
    };
}

namespace SDLTexture
{

class Texture {
        renderer_ptr renderer_;
        str_t        path_;
        texture_ptr  texture_ = nullptr;
        
        point_t pos_;               
        int w = 0;   
        int h = 0;               
    
    public:
        Texture  (const std::string& path, renderer_ptr renderer, int x = 0, int y = 0);
        ~Texture ();

        Texture (const Texture& rhs);
        Texture () : renderer_ (nullptr), path_   ("NO_PATH"),
                     texture_  (nullptr), pos_    ({0 ,0}) {}

        void simple_dump();

        void set_pos (point_t dst);
        void set_demension (int width, int height);

        void move (int delta_x, int delta_y);  

        void draw ();
        void drawframe(int row, int frame);      
};

}

#endif