#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <SDL2/SDL.h>

#include "Widget.hpp"

namespace SDLSettings
{

enum Menu_State
{
    ACTIVE           = 0,
    EXIT             = 1
};

class Settings
{
using renderer_ptr = SDL_Renderer*;

    Menu_State state_ = Menu_State::ACTIVE;
    std::map<std::string, SDLWidget::Button> buttons_;

public:

    Settings() {}

    void loadmedia(renderer_ptr renderer);

    void handle_event(SDL_Event* event);

    void draw();

    Menu_State get_state() { return state_; }

    bool is_active ()      { return state_ == Menu_State::ACTIVE; }
    bool is_nonactive()      { return state_ == Menu_State::EXIT; }

};

}

#endif