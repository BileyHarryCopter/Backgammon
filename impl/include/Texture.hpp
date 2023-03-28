#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct point {
    int x;
    int y;
};

class Texture {
    private:
        SDL_Texture* mTexture = nullptr;
        point pos;  // position on window
        int h = 0;  // height
        int w = 0;  // width
    
    public:
        Texture(std::string path);
        ~Texture();

        void move(point dst);
};

#endif