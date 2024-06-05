#include "../../../includes/ParticuleEssential/Types/Vector2Int.hpp"
#include "../../../includes/ParticuleEssential/Types/Vector2.hpp"
#include <math.h>

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

Vector2Int &Vector2Int::operator*=(const Vector2Int &other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2Int &Vector2Int::operator/=(const Vector2Int &other)
{
    x /= other.x;
    y /= other.y;
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

Vector2Int Vector2Int::operator*(const Vector2Int &other) const
{
    return Vector2Int(x * other.x, y * other.y);
}

Vector2Int Vector2Int::operator/(const Vector2Int &other) const
{
    return Vector2Int(x / other.x, y / other.y);
}

bool Vector2Int::operator==(const Vector2Int &other) const
{
    return x == other.x && y == other.y;
}

bool Vector2Int::operator!=(const Vector2Int &other) const
{
    return x != other.x || y != other.y;
}

Vector2Int::operator Vector2() const
{
    return Vector2((float)x, (float)y);
}

int Vector2Int::Cross(const Vector2Int &other) const
{
    return x * other.y - y * other.x;
}

Vector2Int Vector2Int::Abs() const
{
    return Vector2Int(abs(x), abs(y));
}

int Vector2Int::Dot(const Vector2Int &other) const
{
    return x * other.x + y * other.y;
}

int Vector2Int::Magnitude() const
{
    return sqrt(x * x + y * y);
}

Vector2Int Vector2Int::Normalize() const
{
    int magnitude = Magnitude();
    return Vector2Int(x / magnitude, y / magnitude);
}

Vector2Int Vector2Int::Forward() const
{
    return Vector2Int(0, 1);
}

Vector2Int Vector2Int::Right() const
{
    return Vector2Int(1, 0);
}

Vector2Int Vector2Int::Up() const
{
    return Vector2Int(0, 1);
}