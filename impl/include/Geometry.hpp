#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "CustomException.hpp"

namespace Custom_Exceptions
{
    struct Devision_On_Zero : public Print_Exception
    {
        Devision_On_Zero() : 
            Print_Exception("Devision on zero") {}
    };
}

namespace SDLVector2D
{

struct Vector2D
{
    float x_ = 0.0;
    float y_ = 0.0;

    Vector2D(float x = 0.0, float y = 0.0) : x_{x}, y_{y} {}
    Vector2D(const std::initializer_list<float>& input_list)
    {
        auto input_list_data = input_list.begin();
        if (input_list.size() == 0)
        {
            x_ = 0.0;
            y_ = 0.0;
        }
        if (input_list.size() < 2)
            x_ = input_list_data[0];
        else
        {
            x_ = input_list_data[0];
            y_ = input_list_data[1];
        }
    }

    Vector2D& operator+=(const Vector2D& rhs) 
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& rhs) 
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        return *this;
    }

    Vector2D& operator*=(float value) 
    {
        x_ *= value;
        y_ *= value;
        return *this;
    }

    //  improve to double cmp
    Vector2D& operator/=(float value) 
    {
        if (value == 0.0)
            Custom_Exceptions::Devision_On_Zero{};
        else
        {
            x_ /= value;
            y_ /= value;
        }
        return *this;
    }



};

Vector2D operator+(const Vector2D& lhs, const Vector2D &rhs)
{
    Vector2D tmp = lhs;
    tmp += rhs;
    return tmp;
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) 
{
    Vector2D tmp = lhs;
    tmp -= rhs;
    return tmp;
}

Vector2D operator*(const Vector2D& lhs, float value) 
{
    Vector2D tmp = lhs;
    tmp *= value;
    return tmp;
}
Vector2D operator*(float value, const Vector2D &rhs) { return rhs * value; }

Vector2D operator/(const Vector2D& lhs, float value) 
{
    Vector2D tmp = lhs;
    tmp /= value;
    return tmp;
}


}

#endif
