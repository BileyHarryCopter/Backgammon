#include "Mainloop.hpp"

namespace SDLMainloop
{
//----------
// Creation
//----------
Mainloop::Mainloop() :
    //  SDL initialization
    sdl_{},
    //  Create window
    window_{"Really Armenian Backgammon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE},
    //  Create renderer
    renderer_{window_,  FIRST_SUITABLE, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC}
    {
        //  Set color of background
        renderer_.set_renderer_draw_color(255, 255, 255, 255);

        //  Initialize PNG loading
        int png_flags = IMG_INIT_PNG;
        if (!(IMG_Init(png_flags) & png_flags))
            Custom_Exceptions::IMG_Init_Exception{SDL_GetError()};

        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            Custom_Exceptions::Mix_OpenAudio_Exception{SDL_GetError()};
    }

    bool Mainloop::loadmedia()
    {
        menu_.loadmedia    ("../../impl/assets/menu/menu_media.json",         renderer_.get());
        settings_.loadmedia("../../impl/assets/settings/settings_media.json", renderer_.get());
        game_.loadmedia(renderer_.get());

        scenes_.push(menu_);

        return true;
    }

    void Mainloop::handle_event (SDL_Event * event)
    {
        if (scenes_.empty())
            return;

        std::visit([event](auto &scene)
                   { scene.handle_event(event); },
                   get_active());

        switch (get_active().index())
        {
            case scenes::MENU:
                {
                    auto menu_ptr = std::get_if<SDLMenu::Menu>(&get_active());

                    if (menu_ptr->is_waiting())
                    {
                        menu_ptr->be_active();
                    }
                    else if (menu_ptr->is_moving_to_play())
                    {
                        menu_ptr->be_waiting();

                        scenes_.push(game_);
                    }
                    else if (menu_ptr->is_moving_to_settings())
                    {
                        menu_ptr->be_waiting();

                        settings_.be_active();
                        scenes_.push(settings_);
                    }
                    break;
                }
                break;
            case scenes::SETTINGS:
                {
                    auto settings_ptr = std::get_if<SDLSettings::Settings>(&get_active());
                    if (settings_ptr->is_nonactive())
                    {
                        scenes_.pop();
                    }
                    break;
                } 
                break;
            case scenes::GAME:
            {   
                auto game_ptr = std::get_if<SDLGame::Game>(&get_active());
                if (game_ptr->is_nonactive())
                {
                    scenes_.pop();
                }
                break;
            }
            default:
                break;
        }
    }

    void Mainloop::draw_scene ()
    {
        if (scenes_.empty())
            return;

        std::visit([](auto &active_scene)
                   { active_scene.draw(); },
                   get_active());
    }

    void Mainloop::update(bool *quit_status)
    {
        if (is_exit())
            scenes_.pop();
        
        if (scenes_.empty())
            *quit_status = true;
    }

    bool Mainloop::is_exit()
    {
        return std::visit([](auto &active_scene) -> bool
                          { return active_scene.is_nonactive(); },
                          get_active());
    }

//--------------
// Running loop
//--------------
    void run_backgammon()
    {
        Mainloop mainloop {};
        mainloop.loadmedia();

        bool quit = false;
        SDL_Event event;
        while (!quit)
        {
            while ((SDL_PollEvent(&event) != 0) && (!quit))
            {
                //User requests quit
                if( event.type == SDL_QUIT )
                    quit = true;

                mainloop.handle_event(&event);

                mainloop.update(&quit);
            }

            //  Clear screen
            mainloop.clear_renderer();

            mainloop.draw_scene();

            //  Update screen
            mainloop.present_renderer();
        }
    }

}
