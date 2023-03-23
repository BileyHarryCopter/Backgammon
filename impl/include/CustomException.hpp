#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <SDL2/SDL_error.h>

namespace Backgammon
{

namespace Custom_Exceptions
{

    struct Print_Exception : public std::runtime_error
    {
        Print_Exception(const std::string& msg) : std::runtime_error(msg.data()){}
    };
}

}

#endif
