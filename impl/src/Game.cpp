#include "Game.hpp"

namespace SDLGame
{
    //-----------------
    // Game state info
    //-----------------
        void game_state_info::configure_avaliable_ways() {
            int iter = 0;
            for (auto& way : ways_) {
                if(way_valid(way)) {
                    avaliable_ways[iter] = way;
                    ++iter;
                }
            }
        }
        
        void game_state_info::clean_avaliable_ways() {
            for (auto& valid_way : avaliable_ways) {
                valid_way = 0;
            }
        }

        void game_state_info::clean_ways() {
            for (auto& way : ways_) {
                way = 0;
            }
        }

        //-----------------------------------------------------

        bool game_state_info::way_valid (size_t steps) {
            std::cout << "Validation of " << steps << " steps from " << src_cell_ << std::endl;

            // Validation if src_cell is head, but it's locked:
            if ( ( colour_ == SDLFeature::BLACK ) && 
                 ( src_cell_ == 12              ) &&
                 ( head_is_locked               ) )
            { return false; }

            else if ( ( colour_ == SDLFeature::WHITE ) && 
                      ( src_cell_ == 0               ) &&
                      ( head_is_locked               ) )
            { return false; }

            std::cout << "Passed 1st validation" << std::endl;

            // Validation of finish steps
            if ( ( colour_ == SDLFeature::BLACK          ) &&
                 ( src_cell_ >  black_finish_cell - 6    ) &&
                 ( src_cell_ <= black_finish_cell        ) &&
                 ( src_cell_ + steps > black_finish_cell ) &&
                 ( black_f_in_house < 15                 ) ) 
            { return false; }

            else if ( ( colour_ == SDLFeature::WHITE          ) &&
                      ( src_cell_ > white_finish_cell - 6     ) &&
                      ( src_cell_ <= white_finish_cell        ) &&
                      ( src_cell_ + steps > white_finish_cell ) &&
                      ( white_f_in_house < 15                 ) )
            { return false; }

            std::cout << "Passed 2nd validation" << std::endl;

            // Simple validation of dest_cell colour == src_cell colour:
            SDLFeature::Colour src_cell_c  = cell_activity[src_cell_];
            SDLFeature::Colour dest_cell_c = cell_activity[(src_cell_ + steps) % 24];

            if (dest_cell_c == SDLFeature::NO_COLOR)
                dest_cell_c = src_cell_c;
            
            if (dest_cell_c != src_cell_c)
                return false;
            
            std::cout << "Passed 3d validation" << std::endl;

            return true;
        }

        bool game_state_info::motion_valid (size_t steps) {
            for (auto valid_way : avaliable_ways) {
                if (steps == valid_way) {
                    clean_avaliable_ways();
                    for (auto& way : ways_) {
                        if (way == steps) {
                            way = 0;
                            break;
                        }
                    }
                    return true;
                }
            }

            return false;
        }

        bool game_state_info::check_avaliable_motion() {
            std::cout << "we are in check_avaliable_motion" << std::endl;
            size_t src_cell_cpy = src_cell_; 

            for (size_t cell = 0; cell < 24; ++cell) {
                if (cell_activity[cell] == colour_) {
                    std::cout << "Checking " << cell << " cell" << std::endl;
                    src_cell_ = cell;

                    for (auto way : ways_) {
                        if (way != 0 && way_valid(way)) { 
                            src_cell_ = src_cell_cpy;
                            return true;
                        }
                    }
                }   
            }

            src_cell_ = src_cell_cpy;

            return false;
        }

    //----------
    // Creation
    //----------
        void Game::loadmedia(renderer_ptr renderer) {
            SDLTexture::Texture board ("../../impl/assets/board.png", renderer);
            textures_.insert({"board", board});

            std::vector <SDLTexture::Texture> bf_textures;
            std::vector <SDLFeature::Feature> bfs;
            for (size_t i = 0; i < 15; ++i) {
                bf_textures.push_back({"../../impl/assets/bf.png", renderer});

                bfs.push_back({bf_textures[i], SDLFeature::BLACK});

                field_.push(bfs[i], 12);
            }
            state_.cell_activity[12] = SDLFeature::BLACK;

            std::vector <SDLTexture::Texture> wf_textures;
            std::vector <SDLFeature::Feature> wfs;
            for (size_t i = 0; i < 15; ++i) {
                wf_textures.push_back({"../../impl/assets/wf.png", renderer});

                wfs.push_back({wf_textures[i], SDLFeature::WHITE});

                field_.push(wfs[i], 0);
            }
            state_.cell_activity[0] = SDLFeature::WHITE;

            die_.loadmedia(renderer);
        }

        void game_state_info::show () {
            std::cout << "Game activity = " << activity_ << std::endl
                      << "Colour = "        << colour_   << std::endl
                      << "Source cell = "   << src_cell_
                      << " (" << head_is_locked << ")"      << std::endl
                      << "Dest cell = "     << dest_cell_<< std::endl
                      << "Ways = { " << ways_[0] << ", " << ways_[1]
                      << ", " <<        ways_[2] << ", " << ways_[3] 
                      << "} " << std::endl
                      << "Avaliable ways = { " << avaliable_ways[0] << ", " << avaliable_ways[1]
                      << ", " <<        avaliable_ways[2] << ", " << avaliable_ways[3] 
                      << "} " << std::endl
                      << "White features in house = " << white_f_in_house << std::endl
                      << "Black features in house = " << black_f_in_house << std::endl
                      << "Cell activity: [ ";
                      for (int cell = 0; cell < 24; ++cell) {
                        std::cout << cell_activity[cell] << ", "; 
                      }
                      std::cout << "]" << std::endl << std::endl;

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
        void Game::update_cell_activity() {
            if (state_.colour_ == SDLFeature::BLACK)
                state_.cell_activity[state_.dest_cell_] = SDLFeature::BLACK;
            else if (state_.colour_ == SDLFeature::WHITE)
                state_.cell_activity[state_.dest_cell_] = SDLFeature::WHITE;
            
            if (field_.empty(state_.src_cell_)) {
                state_.cell_activity[state_.src_cell_] = SDLFeature::NO_COLOR;
            }
        }

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
                            }

                            state_.show();
                            break;
                        }
                    case IS_WAITING_SRC_CELL:
                        {   
                            if (state_.check_avaliable_motion()) {
                                size_t mouse_cell = field_.mouse_inside_cell();

                                if (!field_.empty(mouse_cell)     && 
                                     field_.get_cell_colour(mouse_cell) == state_.colour_)
                                {
                                    state_.src_cell_ = mouse_cell;
                                    state_.configure_avaliable_ways();

                                    state_.activity_ = IS_WAITING_DST_CELL;  
                                }
                            }

                            else {
                                state_.switch_colour();
                                state_.clean_ways();

                                state_.activity_ = IS_WAITING_ROLLING_DIE;
                            }

                            state_.show();
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

                                if (state_.motion_valid(steps))
                                {
                                    field_.move_feature(state_.src_cell_, steps);
                                    update_cell_activity();

                                    if ( ( state_.colour_ == SDLFeature::BLACK       ) &&
                                         ( state_.dest_cell_ > black_finish_cell - 6 ) &&
                                         ( state_.dest_cell_ <= black_finish_cell    ) )
                                    { ++state_.black_f_in_house; }

                                    else if ( ( state_.colour_ == SDLFeature::WHITE       ) &&
                                              ( state_.dest_cell_ > white_finish_cell - 6 ) &&
                                              ( state_.dest_cell_ <= white_finish_cell    ) )
                                    { ++state_.white_f_in_house; }   

                                    if (state_.ways_[0] == 0 && state_.ways_[1] == 0 &&
                                        state_.ways_[2] == 0 && state_.ways_[3] == 0)
                                    {
                                        state_.src_cell_   = NO_CELL;
                                        state_.clean_avaliable_ways();
                                        state_.dest_cell_  = NO_CELL;
                                        state_.head_is_locked = false;
                                        state_.switch_colour();

                                        state_.activity_ = IS_WAITING_ROLLING_DIE;
                                    }

                                    else {
                                        if (state_.colour_ == SDLFeature::BLACK && state_.src_cell_ == 12)
                                            state_.head_is_locked = true;
                                        else if (state_.colour_ == SDLFeature::WHITE && state_.src_cell_ == 0)
                                            state_.head_is_locked = true;
                                        
                                        state_.src_cell_   = NO_CELL;
                                        state_.clean_avaliable_ways();
                                        state_.dest_cell_  = NO_CELL;
                                        
                                        state_.activity_ = IS_WAITING_SRC_CELL;
                                    }    
                                }

                                else {
                                    state_.src_cell_   = NO_CELL;
                                    state_.clean_avaliable_ways();
                                    state_.dest_cell_  = NO_CELL;

                                    state_.activity_   = IS_WAITING_SRC_CELL;  
                                }
                            }

                            else {
                                state_.src_cell_  = NO_CELL;
                                state_.clean_avaliable_ways();

                                state_.activity_  = IS_WAITING_SRC_CELL;
                            }

                            state_.show();
                            break;
                        }
                }
            }
        }
}