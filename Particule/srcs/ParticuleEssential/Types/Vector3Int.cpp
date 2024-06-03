#include "../../../includes/ParticuleEssential/Types/Vector3Int.hpp"

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