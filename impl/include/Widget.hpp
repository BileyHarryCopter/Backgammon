#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>
#include "cJSON.h"

#include "Texture.hpp"

namespace SDLWidget
{

//---------
//  BUTTON
//---------
enum Button_State 
{
    BUTTON_SPRITE_MOUSE_OUT         = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN        = 2,
	BUTTON_SPRITE_TOTAL             = 3
};

class Button final
{
using renderer_ptr = SDL_Renderer*;
    std::string                                          label_;
    SDL_Rect                                              rect_;
    Button_State state_ = Button_State::BUTTON_SPRITE_MOUSE_OUT;
    std::vector<SDLTexture::Texture>                  textures_;

public:

    Button(cJSON * createinfo, renderer_ptr renderer);

    void draw();
    void handle_event(SDL_Event *event);
    Button_State get_state() { return state_; }
};


//------------
//  STATUSBAR
//------------
enum Statusbar_State
{
    STATUSBAR_BALANCE = 0,
    STATUSBAR_INCREASE = 1,
    STATUSBAR_DECREASE = 2
};
class Statusbar final
{
using size_t = std::size_t;

    std::string                                          label_;
    SDL_Rect                                              rect_;
    // std::pair<Button, Button>                          buttons_;
    // std::unordered_map<size_t, SDLTexture::Texture>   textures_;
    Statusbar_State state_ = Statusbar_State::STATUSBAR_BALANCE;
    size_t current_, max_;

public:

    Statusbar(cJSON * createinfo, renderer_ptr renderer);

    void draw();
    void handle_event(SDL_Event *event);
    Statusbar_State get_state() { return state_; }
};

}

#endif
