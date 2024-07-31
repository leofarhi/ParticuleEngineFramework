#ifndef VECTOR3_HPP
#define VECTOR3_HPP

class Vector3Int;

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);
    // Constructeur de copie explicite
    Vector3(const Vector3 &other);
    ~Vector3();

    Vector3 &operator=(const Vector3 &other);
    Vector3 &operator+=(const Vector3 &other);
    Vector3 &operator-=(const Vector3 &other);
    Vector3 &operator*=(const Vector3 &other);
    Vector3 &operator/=(const Vector3 &other);
    Vector3 &operator*=(float scalar);
    Vector3 &operator/=(float scalar);

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
    Vector3 operator*(const Vector3 &other) const;
    Vector3 operator/(const Vector3 &other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;
    bool operator==(const Vector3 &other) const;
    bool operator!=(const Vector3 &other) const;

    //Cast operator
    operator Vector3Int() const;

    //Additional methods
    Vector3 Cross(const Vector3 &other) const;
    Vector3 Abs() const;
    float Dot(const Vector3 &other) const;
    float Magnitude() const;
    Vector3 Normalize() const;
    Vector3 Forward() const;
    Vector3 Right() const;
    Vector3 Up() const;
};

#endif // VECTOR3_HPP