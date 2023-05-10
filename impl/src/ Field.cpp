#include "Field.hpp"

namespace SDLField 
{
    void Field::b_peak_setting (int peak, point_t lb_p) {
        point_t med_p     = { lb_p.x + b_peak_w * peak + b_peak_w / 2, 
                              lb_p.y };

        point_t start_p   = { lb_p.x + b_peak_w * peak + b_peak_w / 2 - feature_w/2,
                              lb_p.y - feature_h };

        point_t delta_vec = { (peaks [peak].x - med_p.x) / (num_of_rows - 1),
                              (b_peak_h - feature_h)     / (num_of_rows - 1) };
        

        for (size_t row = 0; row < num_of_rows; ++ row) {
            field_positions[row][peak] = start_p;

            std::cout << "field_positions [" << row << "]["<< peak << "] = {"
                          << field_positions[row][peak].x << ", " 
                          << field_positions[row][peak].y << "}" << std::endl;

            start_p.x += delta_vec.x;
            start_p.y += delta_vec.y;
        }
    }

    Field::Field () {
        for (size_t peak = 0; peak < num_of_cells/4; ++peak) {
            b_peak_setting(peak, l_lb_p);
        }

        std::cout << "\n\n";

        for (size_t peak = num_of_cells/4; peak < num_of_cells/2; ++peak) {
            b_peak_setting (peak, r_lb_p);
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

    size_t Field::mouse_inside_cell () {
        int x, y;
        SDL_GetMouseState(&x, &y);

        Field_Part part;

        if (y >= field_positions[14][0].y)
            part = LOWER;

        else if (y <= (field_positions[14][23].y + feature_h))
            part = UPPER;  
        
        else 
            part = NO_PART;
        
        if (part == LOWER) {
            std::cout << "LOWER part." << std::endl;
            for (size_t cell = 0; cell < num_of_cells/2; ++cell) {

                size_t cell_size;

                if (field_[cell].empty())
                    cell_size = 0;
                else    
                    cell_size = field_[cell].size() - 1;

                if (x < field_positions[0][cell].x)
                    continue;
                
                else if (x > (field_positions[0][cell].x + b_peak_w))
                    continue;

                else if (y > (field_positions[0][cell].y + feature_h))
                    continue;

                else if (y < field_positions[cell_size][cell].y)
                    continue; 
                
                else 
                    return cell;
            }
        }

        else if (part == UPPER) {
            std::cout << "UPPER part." << std::endl;
            for (size_t cell = num_of_cells/2; cell < num_of_cells; ++cell) {

                size_t cell_size;

                if (field_[cell].empty())
                    cell_size = 0;
                else    
                    cell_size = field_[cell].size() - 1;

                if (x < field_positions[0][cell].x)
                    continue;
                
                else if (x > (field_positions[0][cell].x + b_peak_w))
                    continue;

                else if (y > (field_positions[cell_size][cell].y + feature_h))
                    continue;

                else if (y < field_positions[0][cell].y)
                    continue; 
                
                else 
                    return cell;
            }
        }

        return NO_CELL;
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