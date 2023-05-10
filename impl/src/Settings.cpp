#include "Settings.hpp"

namespace SDLSettings
{
    void Settings::loadmedia(const std::string& path, renderer_ptr renderer)
    {
        // //  create Volume nobutton:
        // SDLWidget::Nobutton volume_nobutton ("Volume", {400, 300, 290, 80}, renderer,
        //                                      "../../impl/assets/volume.png");
        // nobuttons_.insert({"Volume", volume_nobutton});

        // //  create Music nobutton:
        // SDLWidget::Nobutton music_nobutton  ("Music", {400, 300, 290, 80}, renderer,
        //                                      "../../impl/assets/music.png");
        // nobuttons_.insert({"Music", music_nobutton});

        // //  create Exit button:
        // SDLWidget::Button exit_button  ("Exit", {700, 660, 290, 80}, renderer,
        //                                 "../../impl/assets/exit_off.png",
        //                                 "../../impl/assets/exit_on.png",
        //                                 "../../impl/assets/exit_on.png");
        // buttons_.insert({"Exit", exit_button});
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
}