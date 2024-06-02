#include "../../../includes/ParticuleEssential/Types/Vector2Int.hpp"

Vector2Int::Vector2Int()
{
    x = 0;
    y = 0;
}

Vector2Int::Vector2Int(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2Int::~Vector2Int()
{
}

Vector2Int &Vector2Int::operator=(const Vector2Int &other)
{
    if (this == &other)
    {
        return *this;
    }
    x = other.x;
    y = other.y;
    return *this;
}

Vector2Int &Vector2Int::operator+=(const Vector2Int &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2Int &Vector2Int::operator-=(const Vector2Int &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2Int &Vector2Int::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2Int &Vector2Int::operator/=(int scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2Int Vector2Int::operator+(const Vector2Int &other) const
{
    return Vector2Int(x + other.x, y + other.y);
}

Vector2Int Vector2Int::operator-(const Vector2Int &other) const
{
    return Vector2Int(x - other.x, y - other.y);
}

Vector2Int Vector2Int::operator*(int scalar) const
{
    return Vector2Int(x * scalar, y * scalar);
}

Vector2Int Vector2Int::operator/(int scalar) const
{
    return Vector2Int(x / scalar, y / scalar);
}

bool Vector2Int::operator==(const Vector2Int &other) const
{
    return x == other.x && y == other.y;
}

bool Vector2Int::operator!=(const Vector2Int &other) const
{
    return x != other.x || y != other.y;
}