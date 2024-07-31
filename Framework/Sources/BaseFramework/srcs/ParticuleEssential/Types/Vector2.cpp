#include "../../../includes/ParticuleEssential/Types/Vector2.hpp"
#include "../../../includes/ParticuleEssential/Types/Vector2Int.hpp"
#include <math.h>

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector2 &other)
{
    x = other.x;
    y = other.y;
}

Vector2::~Vector2()
{
}

Vector2 &Vector2::operator=(const Vector2 &other)
{
    if (this == &other)
    {
        return *this;
    }
    x = other.x;
    y = other.y;
    return *this;
}

Vector2 &Vector2::operator+=(const Vector2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 &Vector2::operator*=(const Vector2 &other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2 &Vector2::operator/=(const Vector2 &other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2 &Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2 &Vector2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const Vector2 &other) const
{
    return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator/(const Vector2 &other) const
{
    return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
    return Vector2(x / scalar, y / scalar);
}

bool Vector2::operator==(const Vector2 &other) const
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2 &other) const
{
    return x != other.x || y != other.y;
}

Vector2::operator Vector2Int() const
{
    return Vector2Int((int)x, (int)y);
}

float Vector2::Cross(const Vector2 &other) const
{
    return x * other.y - y * other.x;
}

Vector2 Vector2::Abs() const
{
    return Vector2(fabs(x), fabs(y));
}

float Vector2::Dot(const Vector2 &other) const
{
    return x * other.x + y * other.y;
}

float Vector2::Magnitude() const
{
    return sqrt(x * x + y * y);
}

Vector2 Vector2::Normalize() const
{
    float mag = Magnitude();
    return Vector2(x / mag, y / mag);
}

Vector2 Vector2::Forward() const
{
    return Vector2(0, 1);
}

Vector2 Vector2::Right() const
{
    return Vector2(1, 0);
}

Vector2 Vector2::Up() const
{
    return Vector2(0, 1);
}