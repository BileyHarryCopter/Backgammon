#include "Widget.hpp"
#include <iostream>


namespace SDLWidget
{

//---------
//  BUTTON
//---------
Button::Button (cJSON * createinfo, renderer_ptr renderer)
{
    label_ = {cJSON_GetObjectItem(createinfo, "label")->valuestring};
    rect_  = {cJSON_GetObjectItem(createinfo, "pos_x")->valueint,
              cJSON_GetObjectItem(createinfo, "pos_y")->valueint,
              cJSON_GetObjectItem(createinfo, "width")->valueint,
              cJSON_GetObjectItem(createinfo, "height")->valueint};

    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_mouse_off")->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_mouse_over")->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_mouse_down")->valuestring,
                                            renderer, rect_.x, rect_.y});
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


// -----------
//  STATUSBAR
// -----------
Statusbar::Statusbar(cJSON * createinfo, renderer_ptr renderer)
{
    
}

}
