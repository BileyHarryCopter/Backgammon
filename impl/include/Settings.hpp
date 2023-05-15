#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <SDL2/SDL.h>

#include "Utility.hpp"
#include "Texture.hpp"
#include "Widget.hpp"

namespace SDLSettings
{

enum Settings_State
{
    ACTIVE           = 0,
    EXIT             = 1
};

class Settings
{
using renderer_ptr    = SDL_Renderer*;

    Settings_State state_    = Settings_State::EXIT;

    std::vector<SDLTexture::Texture>        textures_;
    std::map<std::string, SDLWidget::Button> buttons_;

public:

    Settings() {}

    void loadmedia(const std::string& path, renderer_ptr renderer);

    void handle_event(SDL_Event* event);

    void draw();

    Settings_State get_state() { return state_; }

    void be_active()               { state_ = Settings_State::ACTIVE; }

    bool is_active ()      { return state_ == Settings_State::ACTIVE; }
    bool is_nonactive()      { return state_ == Settings_State::EXIT; }
};

}

#endif