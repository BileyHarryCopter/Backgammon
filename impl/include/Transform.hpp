#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Geometry.hpp"

namespace SDLTransform
{

class Transform
{
    float x_ = 0.0;
    float y_ = 0.0;

public:
    Transform (float x, float y) : x_{x}, y_{y} {}

private:
    void translate (const SDLVector2D::Vector2D& vec)
    {
        x_ += vec.x_;
        y_ += vec.y_;
    }
};

}

#endif