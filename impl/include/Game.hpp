#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <array>
#include <SDL2/SDL.h>
#include "Utility.hpp"

#include "Texture.hpp"
#include "Widget.hpp"
#include "Field.hpp"
#include "Die.hpp"

namespace SDLGame
{
using renderer_ptr  = SDL_Renderer*;
using texture_map_t = std::map<std::string, SDLTexture::Texture>;
using button_map_t  = std::map<std::string, SDLWidget::Button>;
using field_t       = SDLField::Field;
using die_t         = SDLDie::Die;

const int black_finish_cell = 11;
const int white_finish_cell = 23;

const int die_first_center_x = 680;
const int die_second_center_x = 760;
const int die_movement = 200;

enum game_activity
{
    EXIT   = 0,

    IS_WAITING_ROLLING_DIE = 1,
    IS_WAITING_SRC_CELL    = 2,
    IS_WAITING_DST_CELL    = 3
};

const size_t NO_CELL = 24;

struct game_state_info {
    game_activity activity_ = IS_WAITING_ROLLING_DIE;
    int colour_ = SDLFeature::WHITE;

    size_t src_cell_  = NO_CELL;
    bool head_is_locked = false;
    bool drop_is_able = false;
    size_t dest_cell_ = NO_CELL;
    
    std::array <SDLFeature::Colour, 24> cell_activity = {SDLFeature::NO_COLOR};

    std::array<int, 4> ways_ = {0};
    std::array<int, 4> avaliable_ways = {0}; 

    size_t white_f_in_house = 0;
    size_t black_f_in_house = 0;

    size_t black_house_is_full = 0;
    size_t white_house_is_full = 0;

// Work with ways and motions:
    void show();
    void switch_colour() { colour_ *= -1; }

    void configure_avaliable_ways ();
    void clean_avaliable_ways ();
    void clean_ways();

    bool cell_in_black_house(int cell);
    bool cell_in_white_house(int cell);
    bool can_be_droped();
    bool check_for_win();

    bool way_valid (size_t steps);
    bool motion_valid (size_t steps);
    bool check_avaliable_motion ();
};

class Game
{
    game_state_info        state_;
    field_t                field_;
    texture_map_t       textures_;
    button_map_t         buttons_;
    std::pair<die_t, die_t> dies_;

public:
    //----------
    // Creation
    //----------
        Game() {}

        void loadmedia(const std::string& path, renderer_ptr renderer);
        void show_game_state_info ();

    //-----------------------
    // Work with texture map
    //-----------------------
        void set_pos_texture       (const std::string& id, int x, int y);
        void set_demension_texture (const std::string& id, int width, int height);
        void move_texture          (const std::string& id, int delta_x, int delta_y);

        void draw_texture          (const std::string& id);
        
    //-----------------
    // Work with field
    //-----------------
        void move_feature (size_t cell, size_t steps) { field_.move_feature(cell, steps); }
    private:
        void draw_field() { field_.draw_all(); }
    public:

    //----------------
    // Work with dies
    //----------------
        bool is_dies_active(SDL_Event * event);
        std::pair<int, int> dies_status();
    
    //----------
    // Draw all
    //----------
        void draw();

    //------------------
    // Work with events
    //------------------
    private:
        void update_cell_activity();
        void drop ();
    public:
        void handle_event (SDL_Event* event);

        game_state_info get_state() { return state_; }

        bool is_active ()    { return state_.activity_ != game_activity::EXIT; }
        bool is_nonactive()  { return state_.activity_ == game_activity::EXIT; }
};

}

#endif