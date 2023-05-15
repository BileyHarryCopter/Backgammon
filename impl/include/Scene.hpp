#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>
#include <SDL2/SDL.h>

#include "Widget.hpp"

namespace SDLScene
{

enum class Scene_State
{
    ACTIVE = 0,
    EXIT = 1
};

class Scene
{
    
    Scene_State state_ = Scene_State::EXIT;

public:

    

};

}

#endif