#include "Menu.hpp"

namespace SDLMenu
{
    void Menu::loadmedia(const std::string& path, renderer_ptr renderer)
    {
        auto text = Service::readfile(path);
        cJSON *json_data = cJSON_Parse(text.data());

        for (auto node = json_data->child; node != NULL; node = node->next)
        {
            auto type  =  cJSON_GetObjectItem(node, "type")->valuestring;
            auto label = cJSON_GetObjectItem(node, "label")->valuestring;
            if (type == std::string{"Button"})
            {
                SDLWidget::Button button {node, renderer};
                buttons_.insert({label, button});
            }
        }

        cJSON_Delete(json_data);
    }

    void Menu::handle_event(SDL_Event* event)
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
                if (pair.first == "Play")
                    state_ = Menu_State::MOVE_TO_PLAY;
                else if (pair.first == "Settings")
                    state_ = Menu_State::MOVE_TO_SETTINGS;
                else
                    state_ = Menu_State::EXIT;
            }
        }
    }

    void Menu::draw()
    {
        for (auto& pair : buttons_)
        {
            pair.second.draw();
        }
    }

    void Menu::be_active()
    {
        if (is_waiting())
            state_ = Menu_State::ACTIVE;
        else
            throw std::runtime_error{"THROW!"};
    }

    void Menu::be_waiting() 
    {
        if (is_moving_to_play() || is_moving_to_settings())
            state_ = Menu_State::WAITING;
        else 
            throw std::runtime_error{"THROW!"};
    }
}
