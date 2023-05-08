#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <SDL2/SDL.h>

#include "Widget.hpp"

namespace SDLSettings
{

enum Game_State
{
    ACTIVE           = 0,
    EXIT             = 1
};

class Game
{
using renderer_ptr = SDL_Renderer*;

    Game_State state_ = Game_State::ACTIVE;
    std::map<std::string, SDLWidget::Button> buttons_;

public:

    Game() {}

    void loadmedia(renderer_ptr renderer);

    void handle_event(SDL_Event* event);

    void draw();

    Menu_State get_state() { return state_; }

    bool is_active ()      { return state_ == Game_State::ACTIVE; }
    bool is_nonactive()      { return state_ == Game_State::EXIT; }

};

}

#endif