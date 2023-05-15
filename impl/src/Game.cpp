#include "Game.hpp"

namespace SDLGame
{
    //----------
    // Creation
    //----------
        void Game::loadmedia(renderer_ptr renderer) 
        {
            SDLTexture::Texture board ("../../impl/assets/board_test.png", renderer);
            textures_.insert({"board", board});

            std::vector <SDLTexture::Texture> bf_textures;
            std::vector <SDLFeature::Feature> bfs;
            for (size_t i = 0; i < 15; ++i) {
                bf_textures.push_back({"../../impl/assets/bf.png", renderer});

                bfs.push_back({bf_textures[i], SDLFeature::BLACK});

                field_.push(bfs[i], 12);
            }

            std::vector <SDLTexture::Texture> wf_textures;
            std::vector <SDLFeature::Feature> wfs;
            for (size_t i = 0; i < 15; ++i) {
                wf_textures.push_back({"../../impl/assets/wf.png", renderer});

                wfs.push_back({wf_textures[i], SDLFeature::WHITE});

                field_.push(wfs[i], 0);
            }

            die_.loadmedia(renderer);
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

    //----------
    // Draw all
    //----------
        void Game::draw() {
            draw_texture("board");
            draw_field();
            die_.draw();
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
                            die_.handle_event(event);

                            if (die_.is_active())
                            {
                                auto ways = die_.get_status();
                                if (ways.first == ways.second)
                                    state_.ways_.fill(ways.first);
                                else
                                {
                                    state_.ways_[0] = ways.first;
                                    state_.ways_[1] = ways.second;
                                }

                                state_.activity_ = IS_WAITING_SRC_CELL;
                                
                                show_game_state_info();
                            }

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