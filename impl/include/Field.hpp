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

const size_t num_of_cells  = 24;
const size_t num_of_rows   = 15;
const size_t feature_h     = 100;
const size_t feature_w     = 100;
const size_t cell_step     = 91;
const size_t row_step      = 22;
const size_t NO_CELL       = 24;

    enum Field_Part {
        NO_PART = -1,
        UPPER   =  1,
        LOWER   =  0
    };

    class Field {


        feature_map_t field_;
        point_t       field_positions [num_of_rows][num_of_cells];
        point_t       peaks [num_of_cells] = {
            {273,  511}, {345,  511}, {420,  511}, {491,  511}, {563,  511}, {635,  511},
            {806,  511}, {876,  511}, {950,  511}, {1021, 511}, {1095, 511}, {1167, 511},
            {1146, 354}, {1077, 354}, {1005, 354}, {937,  354}, {867,  354}, {798,  354},
            {647,  354}, {577,  354}, {508,  354}, {438,  354}, {368,  354}, {299,  354} 
        };

        public:
            Field();
            ~Field() {};

            void dump ();

            void push (const feature& i_feature, size_t cell = 0);

            void    move_feature       (size_t cur_cell, size_t steps);
            point_t get_field_position (size_t cell, size_t num) { return field_positions [num][cell]; }
            size_t  get_cell_size      (size_t cell)             { return field_[cell].size(); }
            bool    empty              (size_t cell)             { return field_[cell].empty(); }

            size_t mouse_inside_cell ();

            void draw (size_t cell, size_t num);
            void draw_all ();
    };
}

#endif