#include "Game.hpp"

namespace SDLGame
{
    //----------
    // Creation
    //----------
        void Game::loadmedia(const std::string& path, renderer_ptr renderer)
        {
            auto text = Service::readfile(path);
            cJSON *json_data = cJSON_Parse(text.data());

            for (auto node = json_data->child; node != NULL; node = node->next)
            {
                auto type  =  cJSON_GetObjectItem(node, "type")->valuestring;
                auto label = cJSON_GetObjectItem(node, "label")->valuestring;
                if (type == std::string{"Texture"})
                {
                    SDLTexture::Texture texture{cJSON_GetObjectItem(node, "path_to_texture")->valuestring, renderer};
                                                
                    textures_.insert({label, texture});
                }
                else if (type == std::string{"Button"})
                {
                    SDLWidget::Button button {node, renderer};
                    buttons_.insert({label, button});
                }
                else if (type == std::string{"Object"})
                {
                    if (label == std::string{"Die_1"})
                    {
                        dies_.first.loadmedia(node, renderer);
                        std::cout << "\n\nDie_1\n\n";                        
                    }
                    else
                    {
                        dies_.second.loadmedia(node, renderer);
                        std::cout << "\n\nDie_2\n\n";
                    }
                }
            }
            cJSON_Delete(json_data);

            for (auto i = 0; i < 15; ++i)
            {
                field_.push({SDLFeature::Feature{textures_["BF"], SDLFeature::BLACK}}, 12);
                field_.push({SDLFeature::Feature{textures_["WF"], SDLFeature::WHITE}},  0);
            }
        }

        void Game::show_game_state_info () {
            std::cout << "Game activity = " << state_.activity_ << std::endl
                      << "Colour = "        << state_.colour_   << std::endl
                      << "Source cell = "   << state_.src_cell_ << std::endl
                      << "Dest cell = "     << state_.dest_cell_<< std::endl
                      << "Ways = { " << state_.ways_[0] << ", " << state_.ways_[1]
                      <<        ", " << state_.ways_[2] << ", " << state_.ways_[3]
                      <<        "}"                << std::endl << std::endl;

        }
    
    //-----------------------
    // Work with texture map
    //-----------------------
        void Game::set_pos_texture(const std::string& id, int x, int y) {
            textures_[id].set_pos({x, y});
        }

        void Game::set_demension_texture (const std::string& id, int width, int height) {
            textures_[id].set_demension(width, height);
        }

        void Game::move_texture(const std::string& id, int delta_x, int delta_y) {
            textures_[id].move(delta_x, delta_y);
        }

        void Game::draw_texture(const std::string& id) {
            textures_[id].draw();
        }

    //----------------
    // Work with dies
    //----------------
        bool Game::is_dies_active(SDL_Event * event)
        {
            dies_.first.handle_event(event);
            dies_.second.handle_event(event);

            if (dies_.first.is_active() || dies_.second.is_active())
            {
                dies_.first.roll_die();
                dies_.second.roll_die();
                return true;
            }
            return false;
        }
        std::pair<int, int> Game::dies_status()
        {
            return std::pair<int ,int> {dies_.first.get_status(), dies_.second.get_status()};
        }


    //----------
    // Draw all
    //----------
        void Game::draw() {
            draw_texture("Board");
            draw_field();

            dies_.first.draw();
            dies_.second.draw();
        }

    //------------------
    // Work with events
    //------------------
        void Game::handle_event(SDL_Event* event) 
        {
            if (event->type == SDL_MOUSEBUTTONDOWN)
            {
                switch (state_.activity_)
                {
                    case IS_WAITING_ROLLING_DIE:
                        {
                            if (is_dies_active(event))
                            {
                                auto ways = dies_status();
                                if (ways.first == ways.second)
                                    state_.ways_.fill(ways.first);
                                else
                                {
                                    state_.ways_[0] = ways.first;
                                    state_.ways_[1] = ways.second;
                                }

                                state_.activity_ = IS_WAITING_SRC_CELL;
                            }

                            show_game_state_info();
                            break;
                        }
                    case IS_WAITING_SRC_CELL:
                        {
                            if ((state_.src_cell_ == NO_CELL))
                            {
                                size_t mouse_cell = field_.mouse_inside_cell();

                                if (!field_.empty(mouse_cell)     && 
                                     field_.get_cell_colour(mouse_cell) == state_.colour_)
                                {
                                    state_.src_cell_ = mouse_cell;
                                    state_.activity_ = IS_WAITING_DST_CELL;

                                    show_game_state_info();
                                }
                            }
                            break;
                        }
                    case IS_WAITING_DST_CELL:
                        {
                            size_t mouse_cell = field_.mouse_inside_cell();

                            if ((mouse_cell != state_.src_cell_) && (mouse_cell != NO_CELL))
                            {
                                state_.dest_cell_ = mouse_cell;

                                size_t steps;
                                if (state_.dest_cell_ > state_.src_cell_)
                                    steps = state_.dest_cell_ - state_.src_cell_;
                                else 
                                    steps = (SDLField::num_of_cells - state_.src_cell_) + state_.dest_cell_;

                                bool valid_motion = false;
                                for (auto& x : state_.ways_)
                                {
                                    if (steps == x)
                                    {
                                        valid_motion = true;
                                        x = 0;
                                        break;
                                    }
                                }

                                if (valid_motion)
                                {
                                    field_.move_feature(state_.src_cell_, steps);

                                    state_.src_cell_  = NO_CELL;
                                    state_.dest_cell_ = NO_CELL;

                                    if (state_.ways_[0] == 0 && state_.ways_[1] == 0 &&
                                        state_.ways_[2] == 0 && state_.ways_[3] == 0)
                                    {
                                        state_.activity_ = IS_WAITING_ROLLING_DIE;
                                        state_.switch_colour();
                                    }
                                    else
                                        state_.activity_ = IS_WAITING_SRC_CELL;
                                }
                                show_game_state_info();
                                break;
                            }
                        }
                }
            }
        }
}