#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include <vector>
#include <SDL2/SDL.h>

#include "Widget.hpp"

namespace SDLMenu
{

enum MMenu_State
{
    ACTIVE           = 0,
    MOVE_TO_PLAY     = 1,
    MOVE_TO_SETTINGS = 2,
    EXIT             = 3
};

class Menu
{
using renderer_ptr = SDL_Renderer*;

    MMenu_State state_ = MMenu_State::ACTIVE;
    std::map<std::string, SDLWidget::Button> buttons_;

public:
    Menu() {}

    void loadmedia(renderer_ptr renderer);
    //  void loadmedia(const std::string& path_to_json, renderer_ptr renderer);   -   right way

    void handle_event(SDL_Event* event);

    void draw();

    MMenu_State get_state() { return state_; }

    // void update();
    // void clean();
};

}

#endif
