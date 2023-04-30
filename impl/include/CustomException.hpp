#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <SDL2/SDL_error.h>

namespace Custom_Exceptions
{

    struct Base_Exception : public std::runtime_error
    {
        Base_Exception(const std::string& msg) : std::runtime_error(msg.data()){}
    };
    
}

#endif
