#ifndef FIELD_HPP
#define FIELD_HPP

#include <map>
#include <vector>

#include "CustomException.hpp"

#include "Feature.hpp"

namespace Custom_Exceptions
{
    struct Invalid_Cell_Exception : public Base_Exception {
        Invalid_Cell_Exception (const size_t& cell) :
            Base_Exception("Failure of accesing to cell: " + std::to_string(cell)) {}
    };

    struct Invalid_Pos_Exception : public Base_Exception {
        Invalid_Pos_Exception (const size_t& cell, const size_t& num) :
            Base_Exception("Failure of accesing to field position: " + 
                            std::to_string(cell) + " " + std::to_string(num)){}
    };
}

namespace SDLField 
{
using size_t        = std::size_t;
using feature       = SDLFeature::Feature;
using feature_map_t = std::map <size_t, std::vector<feature>>;
using point_t       = SDLTexture::point_t;

const size_t  NO_CELL       = 24;

//----------------
// Field geometry
//----------------
    const int  num_of_cells  = 24;
    const int  num_of_rows   = 15;
    const int  feature_h     = 50;
    const int  feature_w     = 65;

    const point_t peaks [num_of_cells] = {
            {273,  511}, {345,  511}, {420,  511}, {491,  511}, {563,  511}, {635,  511},
            {806,  511}, {876,  511}, {950,  511}, {1021, 511}, {1095, 511}, {1167, 511},
            {1146, 354}, {1077, 354}, {1005, 354}, {937,  354}, {867,  354}, {798,  354},
            {647,  354}, {577,  354}, {508,  354}, {438,  354}, {368,  354}, {299,  354} 
        };

    //--------------
    // Bottom peaks
    //--------------
        const int  b_peak_w = 81;
        const int  b_peak_h = 348;  
        // Left bottom peaks:
            const point_t l_lb_p = {188, 858};
        // Right bottom peaks:
            const point_t r_lb_p = {766, 858};
    //-----------
    // Top peaks
    //-----------
        const int t_peak_w = 64;
        const int t_peak_h = 292;
        // Left top peaks:
            const point_t l_rt_p = {684, 61};
        // Right top peaks:
            const point_t r_rt_p = {1146, 61};


    enum Field_Part {
        NO_PART     = -1,
        UPPER_LEFT  =  0,
        LOWER_LEFT  =  1,
        UPPER_RIGHT =  2,
        LOWER_RIGHT =  3
    };

class Field {
    feature_map_t field_;
    point_t       field_positions [num_of_rows][num_of_cells];

    public:
        //--------------
        // Construction
        //--------------
            Field();
            ~Field() {};
            void b_peak_setting (int peak, point_t lb_p);
            void t_peak_setting (int peak, point_t rt_p);
                
        //------------------
        // Methods for Game
        //------------------
            void push (const feature& i_feature, size_t cell = 0);
            void move_feature (size_t cur_cell, size_t steps);
            size_t mouse_inside_cell ();
        private: 
            size_t part_mouse_search (Field_Part part, int x, int y);
            bool   cell_mouse_search (size_t     cell, int x, int y);
            feature* active_feature_in_cell (size_t cell);
        public:

        //-----------------------
        // Getters and selectors
        //-----------------------
            SDLFeature::Colour  get_cell_colour(size_t cell);
            point_t get_field_position      (size_t cell, size_t num) { return field_positions [num][cell]; }
            size_t  get_cell_size           (size_t cell)             { return field_[cell].size(); }
            bool    empty                   (size_t cell)             { return field_[cell].empty(); }

        //---------
        // Drawers
        //---------
            void draw (size_t cell, size_t num);
            void draw_all ();

        // Dump:
            void dump ();
};
}

#endif