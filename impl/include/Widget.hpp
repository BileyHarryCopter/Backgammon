#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>

#include "Texture.hpp"

namespace SDLWidget
{

struct Widget
{
using renderer_ptr = SDL_Renderer*;

    std::string  label_;
    SDL_Rect      rect_;

    Widget() {}
    Widget (const std::string& label, const SDL_Rect& rect) : label_{label}, rect_{rect} {}

    virtual ~Widget() {}

    void set_position(int x, int y) { rect_.x = x; rect_.y = y; }
};

enum Button_State 
{
    BUTTON_SPRITE_MOUSE_OUT         = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN        = 2,
	BUTTON_SPRITE_TOTAL             = 3
};

class Nobutton final : public Widget 
{
    SDLTexture::Texture texture_;

    Nobutton(const std::string &label, const SDL_Rect &rect, renderer_ptr renderer,
             const std::string &path);

    void draw();
};

class Button final : public Widget
{
    Button_State state_ = Button_State::BUTTON_SPRITE_MOUSE_OUT;
    std::vector<SDLTexture::Texture>                  textures_;

public:
    Button() : Widget{} {};

    Button(const std::string &label, const SDL_Rect &rect,  renderer_ptr renderer, 
                                                            const std::string& mouse_out_path,
                                                            const std::string& mouse_down_path,
                                                            const std::string& mouse_over_path);

    void handle_event(SDL_Event *event);
    void draw();

    Button_State get_state() { return state_; }
};

}

#endif
