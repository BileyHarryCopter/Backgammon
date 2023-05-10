#include "Settings.hpp"

namespace SDLSettings
{
    void Settings::loadmedia(const std::string& path, renderer_ptr renderer)
    {
        auto text = Service::readfile(path);
        cJSON *json_data = cJSON_Parse(text.data());

        for (auto node = json_data->child; node != NULL; node = node->next)
        {
            auto type  =  cJSON_GetObjectItem(node, "type")->valuestring;
            auto label = cJSON_GetObjectItem(node, "label")->valuestring;
            if (type == std::string{"Texture"})
            {
                SDL_Point texture_pos = {cJSON_GetObjectItem(node, "pos_x")->valueint,
                                         cJSON_GetObjectItem(node, "pos_x")->valueint};
                textures_.push_back(SDLTexture::Texture{cJSON_GetObjectItem(node, "path_to_texture")->valuestring,
                                    renderer, texture_pos.x, texture_pos.y});
            }
            else if (type == std::string{"Button"})
            {
                SDLWidget::Button button {node, renderer};
                buttons_.insert({label, button});
            }
        }

        cJSON_Delete(json_data);
    }

    void Settings::handle_event(SDL_Event* event)
    {
        for (auto& pair : buttons_)
        {
            pair.second.handle_event(event);
        }

        for (auto& pair : buttons_)
        {
            auto down_status = pair.second.get_state();
            if (down_status == SDLWidget::Button_State::BUTTON_SPRITE_MOUSE_DOWN)
            {
                if (pair.first == "Exit")
                    state_ = Settings_State::EXIT;
            }
        }
    }

    void Settings::draw()
    {
        for (auto& texture : textures_)
        {
            texture.draw();
        }
        for (auto& pair : buttons_)
        {
            pair.second.draw();
        }
    }
}