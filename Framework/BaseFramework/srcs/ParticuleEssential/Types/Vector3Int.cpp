#include "../../../includes/ParticuleEssential/Types/Vector3Int.hpp"
#include "../../../includes/ParticuleEssential/Types/Vector3.hpp"
#include <math.h>

Vector3Int::Vector3Int()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3Int::Vector3Int(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3Int::~Vector3Int()
{
}

Vector3Int &Vector3Int::operator=(const Vector3Int &other)
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

Vector3Int &Vector3Int::operator+=(const Vector3Int &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3Int &Vector3Int::operator-=(const Vector3Int &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3Int &Vector3Int::operator*=(const Vector3Int &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector3Int &Vector3Int::operator/=(const Vector3Int &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3Int &Vector3Int::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3Int &Vector3Int::operator/=(int scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3Int Vector3Int::operator+(const Vector3Int &other) const
{
    return Vector3Int(x + other.x, y + other.y, z + other.z);
}

Vector3Int Vector3Int::operator-(const Vector3Int &other) const
{
    return Vector3Int(x - other.x, y - other.y, z - other.z);
}

Vector3Int Vector3Int::operator*(const Vector3Int &other) const
{
    return Vector3Int(x * other.x, y * other.y, z * other.z);
}

Vector3Int Vector3Int::operator/(const Vector3Int &other) const
{
    return Vector3Int(x / other.x, y / other.y, z / other.z);
}

Vector3Int Vector3Int::operator*(int scalar) const
{
    return Vector3Int(x * scalar, y * scalar, z * scalar);
}

Vector3Int Vector3Int::operator/(int scalar) const
{
    return Vector3Int(x / scalar, y / scalar, z / scalar);
}

bool Vector3Int::operator==(const Vector3Int &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3Int::operator!=(const Vector3Int &other) const
{
    return x != other.x || y != other.y || z != other.z;
}

Vector3Int::operator Vector3() const
{
    return Vector3((float)x, (float)y, (float)z);
}

Vector3Int Vector3Int::Cross(const Vector3Int &other) const
{
    return Vector3Int(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector3Int Vector3Int::Abs() const
{
    return Vector3Int(abs(x), abs(y), abs(z));
}

int Vector3Int::Dot(const Vector3Int &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

int Vector3Int::Magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3Int Vector3Int::Normalize() const
{
    int magnitude = Magnitude();
    return Vector3Int(x / magnitude, y / magnitude, z / magnitude);
}

Vector3Int Vector3Int::Forward() const
{
    return Vector3Int(0, 0, 1);
}

Vector3Int Vector3Int::Right() const
{
    return Vector3Int(1, 0, 0);
}

Vector3Int Vector3Int::Up() const
{
    return Vector3Int(0, 1, 0);
}