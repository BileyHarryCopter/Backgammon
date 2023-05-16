#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <array>
#include <SDL2/SDL.h>

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

enum game_activity
{
    EXIT   = 0,
    ACTIVE = 1,

    IS_WAITING_ROLLING_DIE = 2,
    IS_WAITING_SRC_CELL    = 3,
    IS_WAITING_DST_CELL    = 4
};

const size_t NO_CELL = 24;

struct game_state_info {
    game_activity activity_ = IS_WAITING_ROLLING_DIE;
    int colour_ = SDLFeature::WHITE;

    size_t src_cell_  = NO_CELL;
    bool head_is_locked = false;
    size_t dest_cell_ = NO_CELL;

    std::array <SDLFeature::Colour, 24> cell_activity = {SDLFeature::NO_COLOR};

    std::array<int, 4> ways_ = {0};
    std::array<int, 4> avaliable_ways = {0}; 

    size_t white_f_in_house = 0;
    size_t black_f_in_house = 0;

// Work with ways and motions:
    void show();
    void switch_colour() { colour_ *= -1; }
    

    void configure_avaliable_ways ();
    void clean_avaliable_ways ();
    void clean_ways();

    bool way_valid (size_t steps);
    bool motion_valid (size_t steps);
    bool check_avaliable_motion ();
};

class Game
{
    game_state_info state_;
    field_t         field_;
    texture_map_t   textures_;
    button_map_t    buttons_;
    die_t           die_;

public:
    //----------
    // Creation
    //----------
        Game() {}

        void loadmedia(renderer_ptr renderer);

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
    
    //----------
    // Draw all
    //----------
        void draw();

    //------------------
    // Work with events
    //------------------
    private:
        void update_cell_activity();
    public:
        void handle_event (SDL_Event* event);
    

        game_state_info get_state() { return state_; }

        bool is_active ()    { return state_.activity_ == game_activity::ACTIVE; }
        bool is_nonactive()  { return state_.activity_ == game_activity::EXIT; }
};

}

#endif