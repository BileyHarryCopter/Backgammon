#ifndef FIELD_HPP
#define FIEALD_HPP

#include <map>
#include <vector>

#include "Feature.hpp"

using feature       = SDLFeature::Feature;
using point_t       = SDL_Point;
using size_t        = std::size_t;
using feature_map_t = std::map <size_t, std::vector<feature>>;

const size_t num_of_cells = 24;
const size_t num_of_rows  = 15;


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
    class Field {
        feature_map_t field_;
        point_t field_positions [num_of_rows][num_of_cells];

        public:
            Field();
            ~Field() {};

            void dump ();

            void push (const feature& i_feature, size_t cell = 0);

            void move_feature (size_t cur_cell, size_t steps);

            void draw (size_t cell, size_t num);
            void draw_all ();
    };
}

#endif