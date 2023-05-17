#include "Die.hpp"

namespace SDLDie
{

void Die::loadmedia(cJSON * createinfo, renderer_ptr renderer)
{
    rect_  = {cJSON_GetObjectItem( createinfo, "pos_x")->valueint,
              cJSON_GetObjectItem( createinfo, "pos_y")->valueint,
              cJSON_GetObjectItem( createinfo, "width")->valueint,
              cJSON_GetObjectItem(createinfo, "height")->valueint};

    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_to_one"  )->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_to_two"  )->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_to_three")->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_to_four" )->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_to_five" )->valuestring,
                                            renderer, rect_.x, rect_.y});
    textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(createinfo, "path_to_six"  )->valuestring,
                                            renderer, rect_.x, rect_.y});

    set_pos(SDL_Point{rect_.x, rect_.y});
}

void Die::handle_event(SDL_Event *event)
{
    if( event->type == SDL_MOUSEBUTTONDOWN )
    {
        int mouse_x = 0, mouse_y = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        bool inside = true;
        if (mouse_x < rect_.x || mouse_x > rect_.x + rect_.w ||
            mouse_y < rect_.y || mouse_y > rect_.y + rect_.h)
            inside = false;

        if ( inside )
        {
            be_active();
            roll_die();
        }
        else
            be_nonactive();
    }
}

void Die::set_pos(SDL_Point pos)
{
    for (auto &texture : textures_)
        texture.set_pos({pos.x, pos.y});
}

void Die::roll_die()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);

    value_  = dist(gen);
}

void Die::draw()
{
    //  This "-1" is really important trick
    textures_[value_ - 1].draw();
}

}
