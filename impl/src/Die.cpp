#include "Die.hpp"

namespace SDLDie
{

void Die::handle_event(SDL_Event *event)
{
    if( event->type == SDL_MOUSEBUTTONDOWN )
    {
        int mouse_x = 0, mouse_y = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        bool inside = true;
        if (mouse_x < rect_.x || mouse_x > rect_.x + rect_.w ||
            mouse_y < rect_.y || mouse_y > rect_.y + rect_.h)
            inside = false;

        if ( inside )
        {
            be_active();
            roll_die();
        }
        else
            be_nonactive();
    }
}

void Die::roll_die()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);

    val_first  = dist(gen);
    val_second = dist(gen);
}

void Die::loadmedia(renderer_ptr renderer)
{
    rect_ = SDL_Rect{100, 100, 50, 50};
    renderer_ = renderer;
}

void Die::draw()
{
    SDL_SetRenderDrawColor( renderer_, 0x00, 0xFF, 0x00, 0xFF );		
    SDL_RenderDrawRect( renderer_, &rect_ );
}

}