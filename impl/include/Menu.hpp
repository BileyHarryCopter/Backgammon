#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include <vector>
#include <SDL2/SDL.h>

#include "Widget.hpp"

namespace SDLMenu
{

enum Menu_State
{
    ACTIVE           = 0,
    MOVE_TO_PLAY     = 1,
    MOVE_TO_SETTINGS = 2,
    EXIT             = 3
};

class Menu
{
using renderer_ptr = SDL_Renderer*;

    Menu_State state_ = Menu_State::ACTIVE;
    std::map<std::string, SDLWidget::Button> buttons_;

public:
    Menu() {}

    void loadmedia(renderer_ptr renderer);
    //  void loadmedia(const std::string& path_to_json, renderer_ptr renderer);   -   right way

    void handle_event(SDL_Event* event);

    void draw();

    Menu_State get_state() { return state_; }

    bool is_active ()                      { return state_ == Menu_State::ACTIVE; }
    bool is_nonactive()                      { return state_ == Menu_State::EXIT; }
    bool is_moving_to_play()         { return state_ == Menu_State::MOVE_TO_PLAY; }
    bool is_moving_to_settings() { return state_ == Menu_State::MOVE_TO_SETTINGS; }

};

}

#endif
