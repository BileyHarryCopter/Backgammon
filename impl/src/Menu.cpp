#include "Menu.hpp"

namespace SDLMenu
{
    void Menu::loadmedia(renderer_ptr renderer)
    {
        //  create Play button:
        SDLWidget::Button play_button  ("Play", {500, 300, 290, 80}, renderer,
                                        "../../impl/assets/play_off.png",
                                        "../../impl/assets/play_on.png",
                                        "../../impl/assets/play_on.png");
        buttons_.insert({"Play", play_button});

        //  create Settings button:
        SDLWidget::Button settings_button  ("Settings", {500, 380, 290, 80}, renderer,
                                        "../../impl/assets/settings_off.png",
                                        "../../impl/assets/settings_on.png",
                                        "../../impl/assets/settings_on.png");
        buttons_.insert({"Settings", settings_button});

        //  create Exit button:
        SDLWidget::Button exit_button  ("Exit", {500, 460, 290, 80}, renderer,
                                        "../../impl/assets/exit_off.png",
                                        "../../impl/assets/exit_on.png",
                                        "../../impl/assets/exit_on.png");
        buttons_.insert({"Exit", exit_button});
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

    // void Menu::update()
    // {
    // }

    // void Menu::clean()
    // {
    // }
}
