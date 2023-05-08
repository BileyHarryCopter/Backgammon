#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

#include "CustomException.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Feature.hpp"
#include "Field.hpp"
#include "Menu.hpp"

using size_t         = std::size_t;
using music_ptr      = Mix_Music *;
using renderer_ptr   = SDL_Renderer *;
using texture_map_t  = std::map<std::string, SDLTexture::Texture>;

namespace Custom_Exceptions
{
    struct SDL_Init_Exception : public Base_Exception
    {
        SDL_Init_Exception(const std::string& error_msg) :
            Base_Exception("Failure of initialization of SDL Library with error: " + error_msg) {}
    };

    struct IMG_Init_Exception : public Base_Exception
    {
        IMG_Init_Exception(const std::string& error_msg) :
            Base_Exception("Failure with initialization of SDL_image: " + error_msg) {}
    };

    struct Mix_OpenAudio_Exception : public Base_Exception
    {
        Mix_OpenAudio_Exception(const std::string& error_msg) :
            Base_Exception("Failure with initialization of SDL_mixer: " + error_msg) {}
    };
}

namespace SDLMainloop
{

struct SDL {
    SDL() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
            Custom_Exceptions::SDL_Init_Exception{SDL_GetError()};
    }

    ~SDL() { SDL_Quit(); }
};

class Mainloop {
    music_ptr       music_ = nullptr;
    SDL             sdl_;
    Window          window_;
    Renderer        renderer_;
    SDLField::Field field_;
    texture_map_t   textures_;

    SDLMenu::Menu                             main_menu_;

    public:
        //----------
        // Creation
        //----------
            Mainloop();
            ~Mainloop();
    public:
        //----------
        // Creation
        //----------
            Mainloop();
            ~Mainloop();

            bool loadmedia();
            bool loadmedia();

        //--------------------
        // Work with Renderer
        //--------------------
            void clear_renderer()   { renderer_.render_clear(); }
            void present_renderer() { renderer_.render_present(); }
            renderer_ptr get_renderer() { return renderer_.get(); }
        //--------------------
        // Work with Renderer
        //--------------------
            void clear_renderer()   { renderer_.render_clear(); }
            void present_renderer() { renderer_.render_present(); }
            renderer_ptr get_renderer() { return renderer_.get(); }

        //--------------------
        // Work with textures
        //--------------------
            void set_pos_texture       (const std::string& id, int x, int y);
            void set_demension_texture (const std::string& id, int width, int height);
        //--------------------
        // Work with textures
        //--------------------
            void set_pos_texture       (const std::string& id, int x, int y);
            void set_demension_texture (const std::string& id, int width, int height);

            void move_texture          (const std::string& id, int delta_x, int delta_y);
            void move_texture          (const std::string& id, int delta_x, int delta_y);

            void draw_texture          (const std::string& id);
            void draw_frame_texture    (const std::string& id, int row, int frame);
            void draw_texture          (const std::string& id);
            void draw_frame_texture    (const std::string& id, int row, int frame);

        //-----------------
        // Work with field
        //-----------------
            void draw_field   ()                          { field_.draw_all(); }
            void move_feature (size_t cell, size_t steps) { field_.move_feature(cell, steps); }
                                            
            //  This should be proccessed on the active scene
            void handle_event (SDL_Event * event) {main_menu_.handle_event(event);}
            void draw_scene() { main_menu_.draw(); }

    private:
        SDLTexture::Texture& get_texture(const std::string &id) { return textures_.at(id); }

};

//--------------
// Running loop
//--------------
    void run_backgammon();

}

#endif

