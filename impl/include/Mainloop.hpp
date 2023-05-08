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
#include "Game.hpp"
#include "Scene.hpp"

using size_t         = std::size_t;
using music_ptr      = Mix_Music *;
using renderer_ptr   = SDL_Renderer *;
using texture_map_t  = std::map<std::string, SDLTexture::Texture>;
using menu_t         = SDLMenu::Menu;
using game_t         = SDLGame::Game;
using scene_stack_t  = SDLScene::Scene;

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
    music_ptr     music_ = nullptr;
    SDL           sdl_;
    Window        window_;
    Renderer      renderer_;
    menu_t        menu_;
    // SDLGame::Game                 game_;
    scene_stack_t scenes_;

    public:
        //----------
        // Creation
        //----------
            Mainloop();
            ~Mainloop();
            bool loadmedia();

    game_t game_;

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

//--------------------
// Work with Renderer
//--------------------
    void clear_renderer()   { renderer_.render_clear(); }
    void present_renderer() { renderer_.render_present(); }
    renderer_ptr get_renderer() { return renderer_.get(); }
                        
    //  This should be proccessed on the active scene
    void handle_event (SDL_Event * event) {menu_.handle_event(event);}
    void draw_scene() { menu_.draw(); }

    //  This should be deleted
    void update(bool *quit_status);

};

//--------------
// Running loop
//--------------
    void run_backgammon();

}

#endif

