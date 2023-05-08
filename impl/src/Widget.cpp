#include "Widget.hpp"
#include <iostream>


namespace SDLWidget
{

Nobutton::Nobutton (const std::string &label, const SDL_Rect &rect, renderer_ptr renderer,
                    const std::string &path) : Widget (label, rect), texture_(path, renderer, rect_.x, rect_.y)
{}

void Nobutton::draw()
{
    texture_.draw();
}

Button::Button (const std::string& label, const SDL_Rect &rect, renderer_ptr renderer,
                                                                const std::string& mouse_out_path,
                                                                const std::string& mouse_down_path,
                                                                const std::string& mouse_over_path) : 
        Widget (label, rect)
{
    SDLTexture::Texture mouse_out  (mouse_out_path,  renderer, rect_.x, rect_.y);
    SDLTexture::Texture mouse_over (mouse_over_path, renderer, rect_.x, rect_.y);
    SDLTexture::Texture mouse_down (mouse_down_path, renderer, rect_.x, rect_.y);

    textures_.push_back(mouse_out);
    textures_.push_back(mouse_over);
    textures_.push_back(mouse_down);
}

void Button::handle_event(SDL_Event* event)
{
    if( event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_x = 0, mouse_y = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        bool inside = true;
        if (mouse_x < rect_.x || mouse_x > rect_.x + rect_.w ||
            mouse_y < rect_.y || mouse_y > rect_.y + rect_.h)
            inside = false;

        if ( !inside )
            state_ = Button_State::BUTTON_SPRITE_MOUSE_OUT;
        else
            {
                switch (event->type)
                {
                case SDL_MOUSEMOTION:
					state_ = Button_State::BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
			
				case SDL_MOUSEBUTTONDOWN:
					state_ = Button_State::BUTTON_SPRITE_MOUSE_DOWN;
					break;

                default:
                    state_ = Button_State::BUTTON_SPRITE_MOUSE_OUT;
					break;
            }
        }
    }
    else
        return;
}

void Button::draw()
{
    textures_[state_].draw();
}

}
