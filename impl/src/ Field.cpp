#include "Field.hpp"

namespace SDLField 
{
    Field::Field () {
        size_t row_step    = 24;
        size_t column_step = 91;

        size_t i;
        size_t j;
        
        point_t start_p = {140, 60};
        for (i = 0; i < num_of_rows; ++i) {
            for (j = 0; j < num_of_cells/4; ++j) {
                field_positions[i][j] = start_p;
                start_p.x += column_step;
            }
            start_p.x = 140;
            start_p.y += row_step;
        }
        
        start_p = {743, 60};
        for (i = 0; i < num_of_rows; ++i) {
            for (j = num_of_cells/4; j < num_of_cells/2; ++j) {
                field_positions[i][j] = start_p;
                start_p.x += column_step;
            }
            start_p.x = 743;
            start_p.y += row_step;
        }

        start_p = {140, 800};
        for (i = 0; i < num_of_rows; ++i) {
            for (j = num_of_cells/2; j < 3*num_of_cells/4; ++j) {
                field_positions[i][j] = start_p;
                start_p.x += column_step;
            }
            start_p.x = 140;
            start_p.y -= row_step;
        }

        start_p = {743, 800};
        for (i = 0; i < num_of_rows; ++i) {
            for (j = 3*num_of_cells/4; j < num_of_cells; ++j) {
                field_positions[i][j] = start_p;
                start_p.x += column_step;
            }
            start_p.x = 743;
            start_p.y -= row_step;
        }
    }

    void Field::dump() {
        for (size_t cell = 0; cell < num_of_cells; ++cell) {
            if (field_[cell].empty()) continue;

            std::cout << "CELL " << cell << " -----------------------" << std::endl;

            size_t size = field_[cell].size();

            for (size_t num = 0; num < size; ++num) {
                field_[cell][num].dump();
                std::cout << std::endl;
            }
        }
    }

    void Field::push (const feature& i_feature, size_t cell) {
        if (cell > num_of_cells)
            throw Custom_Exceptions::Invalid_Cell_Exception {cell};

        field_[cell].push_back(i_feature);

        size_t cell_num = field_[cell].size() - 1;

        field_[cell].back().set_texture_pos(field_positions[cell_num][cell]);
    }

    void Field::move_feature (size_t cur_cell, size_t steps) {
        if ((cur_cell > num_of_cells) || (field_[cur_cell].empty()))
            throw Custom_Exceptions::Invalid_Cell_Exception {cur_cell};

        feature& cur_feature = field_[cur_cell].back();

        size_t dst_cell = (cur_cell + steps) % num_of_cells;
        
        field_[dst_cell].push_back(cur_feature);
        size_t dst_cell_len = field_[dst_cell].size();

        field_[cur_cell].pop_back();
        field_[dst_cell].back().set_texture_pos(field_positions[dst_cell_len - 1][dst_cell]); 
    }

    void Field::draw (size_t cell, size_t num) {
        if ((cell > num_of_cells) || (field_[cell].empty()))
            throw Custom_Exceptions::Invalid_Cell_Exception {cell};
        if (num > field_[cell].size())
            throw Custom_Exceptions::Invalid_Pos_Exception {cell, num};
        
        field_[cell][num].draw();
    }

    void Field::draw_all () {
        for (size_t cell = 0; cell < num_of_cells; ++cell) {
            if (field_[cell].empty()) continue;

            size_t size = field_[cell].size();

            for (size_t num = 0; num < size; ++num) {
                field_[cell][num].draw();
            }
        }
    }
}