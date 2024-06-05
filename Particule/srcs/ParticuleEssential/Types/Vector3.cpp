#include "../../../includes/ParticuleEssential/Types/Vector3.hpp"
#include "../../../includes/ParticuleEssential/Types/Vector3Int.hpp"
#include <math.h>

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::~Vector3()
{
}

Vector3 &Vector3::operator=(const Vector3 &other)
{
    if (this == &other)
    {
        return *this;
    }
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector3 &Vector3::operator+=(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3 &Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 &Vector3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) const
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(const Vector3 &other) const
{
    return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(float scalar) const
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

bool Vector3::operator==(const Vector3 &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3 &other) const
{
    return x != other.x || y != other.y || z != other.z;
}

Vector3::operator Vector3Int() const
{
    return Vector3Int((int)x, (int)y, (int)z);
}

Vector3 Vector3::Cross(const Vector3 &other) const
{
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector3 Vector3::Abs() const
{
    return Vector3(abs(x), abs(y), abs(z));
}

float Vector3::Dot(const Vector3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vector3::Magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Normalize() const
{
    int magnitude = Magnitude();
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

Vector3 Vector3::Forward() const
{
    return Vector3(0, 0, 1);
}

Vector3 Vector3::Right() const
{
    return Vector3(1, 0, 0);
}

Vector3 Vector3::Up() const
{
    return Vector3(0, 1, 0);
}