#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <SDL2/SDL.h>

#include "CustomException.hpp"

#include "Texture.hpp"
#include "Widget.hpp"
#include "Feature.hpp"
#include "Field.hpp"

namespace SDLGame
{

enum Game_State
{
    ACTIVE           = 0,
    EXIT             = 1
};

class Game
{
using renderer_ptr  = SDL_Renderer*;
using texture_map_t = std::map<std::string, SDLTexture::Texture>;
    Game_State state_ = Game_State::ACTIVE;

    SDLField::Field                            field_;
    texture_map_t                           textures_;
    std::map<std::string, SDLWidget::Button> buttons_;

public:

    Game() {}

    void loadmedia(renderer_ptr renderer);

    void handle_event(SDL_Event* event);

    void draw();

    Game_State get_state() { return state_; }

    bool is_active ()  { return state_ == Game_State::ACTIVE; }
    bool is_nonactive()  { return state_ == Game_State::EXIT; }

    void draw_texture(const std::string& id);

//-----------------
// Work with field
//-----------------
    void move_feature (size_t cell, size_t steps) { field_.move_feature(cell, steps); }

private:
    SDLTexture::Texture& get_texture(const std::string &id) { return textures_.at(id); }

    void draw_field() { field_.draw_all(); }

};

}

#endif