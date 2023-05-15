#include "Field.hpp"

namespace SDLField 
{
//--------------
// Construction
//--------------
    Field::Field () {
        for (size_t peak = 0; peak < num_of_cells/4; ++peak) {
            b_peak_setting(peak, l_lb_p);
        }

        std::cout << "\n\n";

        for (size_t peak = num_of_cells/4; peak < num_of_cells/2; ++peak) {
            b_peak_setting (peak, r_lb_p);
        }

        std::cout << "\n\n";

        for (size_t peak = num_of_cells/2; peak < 3*num_of_cells/4; ++peak) {
            t_peak_setting (peak, r_rt_p);
        }

        std::cout << "\n\n";

        for (size_t peak = 3*num_of_cells/4; peak < num_of_cells; ++peak) {
            t_peak_setting (peak, l_rt_p);
        }  
    }

    void Field::b_peak_setting (int peak, point_t lb_p) {
        int step = peak % 6;

        point_t med_p     = { lb_p.x + b_peak_w * step + b_peak_w / 2, 
                              lb_p.y };

        point_t start_p   = { med_p.x - feature_w/2,
                              lb_p.y  - feature_h };

        point_t delta_vec = { (peaks [peak].x - med_p.x) / (num_of_rows - 1),
                              (b_peak_h - feature_h)     / (num_of_rows - 1) };
        

        for (size_t row = 0; row < num_of_rows; ++ row) {
            field_positions[row][peak] = start_p;

            std::cout << "field_positions [" << row << "]["<< peak << "] = {"
                            << field_positions[row][peak].x << ", " 
                            << field_positions[row][peak].y << "}" << std::endl;

            start_p.x += delta_vec.x;
            start_p.y -= delta_vec.y;
        }
    }

    void Field::t_peak_setting (int peak, point_t rt_p) {
        int step;

        if (peak < 18) 
            step = peak % 12;
        else
            step = peak % 18;

        point_t med_p     = { rt_p.x - t_peak_w * step - t_peak_w/2,
                              rt_p.y };
        
        point_t start_p   = { med_p.x - feature_w/2, 
                              rt_p.y };

        point_t delta_vec = { (peaks[peak].x - med_p.x) / (num_of_rows - 1),
                              (t_peak_h - feature_h)    / (num_of_rows - 1) };
        
        for (size_t row = 0; row < num_of_rows; ++ row) {
            field_positions[row][peak] = start_p;

            std::cout << "field_positions [" << row << "]["<< peak << "] = {"
                          << field_positions[row][peak].x << ", " 
                          << field_positions[row][peak].y << "}" << std::endl;

            start_p.x += delta_vec.x;
            start_p.y += delta_vec.y;
        }
    }

//------------------
// Methods for Game
//------------------    
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

        if      ( (y >= field_positions[14][0].y)               &&
                  (y <= field_positions[0][0].y + feature_h)    && 
                  (x <= field_positions[0][5].x + feature_w)    &&
                  (x >= field_positions[0][0].x) ) 
        { part = LOWER_LEFT; 
          std::cout << "LOWER_LEFT part" << std::endl; }
        
        else if ( (y >= field_positions[14][6].y)               &&
                  (y <= field_positions[0][6].y  + feature_h)   && 
                  (x <= field_positions[0][11].x + feature_w)   &&
                  (x >= field_positions[14][6].x) ) 
        { part = LOWER_RIGHT; 
          std::cout << "LOWER_RIGHT part" << std::endl; } 

        else if ( (y >= field_positions[0][23].y)               &&
                  (y <= field_positions[14][23].y + feature_h)  && 
                  (x <= field_positions[0][18].x  + feature_w)  &&
                  (x >= field_positions[14][23].x) ) 
        { part = UPPER_LEFT; 
          std::cout << "UPPER_LEFT part" << std::endl; } 

        else if ( (y >= field_positions[0][17].y)               &&
                  (y <= field_positions[14][17].y  + feature_h) && 
                  (x <= field_positions[14][12].x  + feature_w) &&
                  (x >= field_positions[0][17].x) ) 
        { part = UPPER_RIGHT; 
          std::cout << "UPPER_RIGHT part" << std::endl;} 
        
        else 
        { part = NO_PART; }

        if (part != NO_PART) {
            return part_mouse_search (part, x, y);
        }

        return NO_CELL;
    }

    size_t Field::part_mouse_search (Field_Part part, int x, int y) {
        size_t start_cell  = 0;
        size_t finish_cell = num_of_cells / 4;

        if (part == LOWER_RIGHT) {
            start_cell  += num_of_cells / 4;
            finish_cell += num_of_cells / 4;
        }

        else if (part == UPPER_RIGHT) {
            start_cell  += num_of_cells / 2;
            finish_cell += num_of_cells / 2;
        }
        
        else if (part == UPPER_LEFT) {
            start_cell  += 3 * num_of_cells / 4;
            finish_cell += 3 * num_of_cells / 4;
        }
        
        for ( ; start_cell < finish_cell; ++start_cell) {
            if(cell_mouse_search(start_cell, x, y))
                return start_cell;
        }

        return NO_CELL;
    }

    bool Field::cell_mouse_search (size_t cell, int x, int y) {
        size_t features_for_check = field_[cell].size();
    
        if(features_for_check == 0)
            features_for_check = 1;
        
        for (size_t feature = 0; feature < features_for_check; ++feature) {
            bool inside = true;

            if (x >= (field_positions[feature][cell].x + feature_w))
                inside = false;
            if (x <= (field_positions[feature][cell].x))
                inside = false;
            if (y >= (field_positions[feature][cell].y + feature_h))
                inside = false;
            if (y <= (field_positions[feature][cell].y))
                inside = false;
            
            if (inside)
                return inside;
        }

        return false;
    }

    feature* Field::active_feature_in_cell (size_t cell)
    {
        if ( field_[cell].empty())
            return nullptr;
        else 
            return &field_[cell].back();
    }

//-----------------------
// Getters and selectors
//-----------------------

    SDLFeature::Colour Field::get_cell_colour(size_t cell)
    {
        auto current_feature = active_feature_in_cell(cell);
        if (current_feature == nullptr)
            return SDLFeature::NO_COLOR;
        else
            return current_feature->get_colour();
    }

//---------
// Drawers
//---------
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

// Dump:
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
}