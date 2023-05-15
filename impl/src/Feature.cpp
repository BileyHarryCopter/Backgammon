#include "Feature.hpp"

namespace SDLFeature
{

void Feature::dump()
{
    texture_.simple_dump();
    std::cout << "Colour = " << colour_ << std::endl;
}

}