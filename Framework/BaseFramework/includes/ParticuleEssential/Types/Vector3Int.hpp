#ifndef VECTOR3INT_HPP
#define VECTOR3INT_HPP

class Vector3;

class Vector3Int
{
public:
    int x;
    int y;
    int z;

    Vector3Int();
    Vector3Int(int x, int y, int z);
    ~Vector3Int();

    Vector3Int &operator=(const Vector3Int &other);
    Vector3Int &operator+=(const Vector3Int &other);
    Vector3Int &operator-=(const Vector3Int &other);
    Vector3Int &operator*=(const Vector3Int &other);
    Vector3Int &operator/=(const Vector3Int &other);
    Vector3Int &operator*=(int scalar);
    Vector3Int &operator/=(int scalar);

    Vector3Int operator+(const Vector3Int &other) const;
    Vector3Int operator-(const Vector3Int &other) const;
    Vector3Int operator*(const Vector3Int &other) const;
    Vector3Int operator/(const Vector3Int &other) const;
    Vector3Int operator*(int scalar) const;
    Vector3Int operator/(int scalar) const;
    bool operator==(const Vector3Int &other) const;
    bool operator!=(const Vector3Int &other) const;

    //Cast operator
    operator Vector3() const;

    //Additional methods
    Vector3Int Cross(const Vector3Int &other) const;
    Vector3Int Abs() const;
    int Dot(const Vector3Int &other) const;
    int Magnitude() const;
    Vector3Int Normalize() const;
    Vector3Int Forward() const;
    Vector3Int Right() const;
    Vector3Int Up() const;
    
};

#endif // VECTOR3INT_HPP