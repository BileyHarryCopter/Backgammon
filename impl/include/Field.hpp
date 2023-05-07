#ifndef FIELD_HPP
#define FIEALD_HPP

#include <map>
#include <vector>

#include "Feature.hpp"

using feature  = SDLFeature::Feature;
using point_t  = SDL_Point;
using size_t   = std::size_t;

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

const size_t max_num_of_cells = 24;
const size_t rows             = 12;
const size_t columns          = 30;

namespace SDLField {

    class Field {
        std::map <size_t, std::vector<feature>> field_;
        point_t field_positions [rows][columns];

        public:
            Field()  {
                field_positions[0][0] = {200, 100};
                field_positions[1][0] = {400, 100};
                // setting positons on screen
            }
            ~Field() {}

            void dump () {
                for (size_t cell = 0; cell < max_num_of_cells; ++cell) {
                    if (field_[cell].empty()) continue;

                    std::cout << "CELL " << cell << " -----------------------" << std::endl;

                    size_t size = field_[cell].size();

                    for (size_t num = 0; num < size; ++num) {
                        field_[cell][num].dump();
                        std::cout << std::endl;
                    }
                }
            }

            void push (const feature& i_feature, size_t cell = 0) {
                if (cell > max_num_of_cells)
                    throw Custom_Exceptions::Invalid_Cell_Exception {cell};

                field_[cell].push_back(i_feature);

                size_t cell_num = field_[cell].size() - 1;

                field_[cell].back().set_texture_pos(field_positions[cell][cell_num]);
            }

            void move_feature (size_t cur_cell, size_t steps) {
                if ((cur_cell > max_num_of_cells) || (field_[cur_cell].empty()))
                    throw Custom_Exceptions::Invalid_Cell_Exception {cur_cell};

                feature& cur_feature = field_[cur_cell].back();

                int dst_cell         = (cur_cell + steps) % max_num_of_cells;
                
                field_[dst_cell].push_back(cur_feature);
                size_t dst_cell_len = field_[dst_cell].size();

                field_[cur_cell].pop_back();
                field_[dst_cell].back().set_texture_pos(field_positions[dst_cell][dst_cell_len - 1]);
            }

            void draw_all () {
                for (size_t cell = 0; cell < max_num_of_cells; ++cell) {
                    if (field_[cell].empty()) continue;

                    size_t size = field_[cell].size();

                    for (size_t num = 0; num < size; ++num) {
                        field_[cell][num].draw();
                    }
                }
            }

            void draw (size_t cell, size_t num) {
                if ((cell > max_num_of_cells) || (field_[cell].empty()))
                    throw Custom_Exceptions::Invalid_Cell_Exception {cell};
                if (num > field_[cell].size())
                    throw Custom_Exceptions::Invalid_Pos_Exception {cell, num};
                
                field_[cell][num].draw();
            }
    };

}

#endif