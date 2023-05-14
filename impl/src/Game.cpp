#include "Game.hpp"

namespace SDLGame
{
    //----------
    // Creation
    //----------
        void Game::loadmedia(renderer_ptr renderer) {
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
        }

        void Game::show_game_state_info () {
            std::cout << "Game activity = " << state_.activity_ << "\n" 
                      << "Motion = "        << state_.motion_   << "\n" 
                      << "Source cell = "   << state_.src_cell_ << "\n" 
                      << "Dest cell = "     << state_.dest_cell_<< std::endl;
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
        }
    
    //------------------
    // Work with events
    //------------------
        void Game::handle_event(SDL_Event* event) {
            if ( event -> type == SDL_MOUSEBUTTONDOWN ) 
            {
                std::cout << "Catch mouse button down." << std::endl; 
                show_game_state_info();

                if (state_.src_cell_ == NO_CELL) {
                    std::cout << "No src cell branch." << std::endl;

                    size_t mouse_cell = field_.mouse_inside_cell();
                    std::cout << "Mouse inside " << mouse_cell << " cell. \n" << std::endl;

                    if (!field_.empty(mouse_cell)) {
                        state_.src_cell_ = mouse_cell;
                        show_game_state_info();
                    }
                }

                else {
                    std::cout << "Src cell branch." << std::endl;

                    size_t mouse_cell = field_.mouse_inside_cell();
                    std::cout << "Mouse inside " << mouse_cell << " cell. \n" << std::endl;

                    if ((mouse_cell != state_.src_cell_) && (mouse_cell != NO_CELL)) {
                        state_.dest_cell_ = mouse_cell;
                        show_game_state_info();

                        size_t steps;

                        if (state_.dest_cell_ > state_.src_cell_)
                            steps = state_.dest_cell_ - state_.src_cell_;
                        
                        else 
                            steps = (SDLField::num_of_cells - state_.src_cell_) + state_.dest_cell_;

                        field_.move_feature(state_.src_cell_, steps);

                        state_.src_cell_  = NO_CELL;
                        state_.dest_cell_ = NO_CELL; 
                        show_game_state_info();
                    }

                    else {
                        state_.src_cell_  = NO_CELL;
                        state_.dest_cell_ = NO_CELL;
                        show_game_state_info(); 
                    }
                }
            }
        }
}