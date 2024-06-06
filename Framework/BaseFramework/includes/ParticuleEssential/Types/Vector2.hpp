#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2Int;

class Vector2
{
public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    ~Vector2();

    Vector2 &operator=(const Vector2 &other);
    Vector2 &operator+=(const Vector2 &other);
    Vector2 &operator-=(const Vector2 &other);
    Vector2 &operator*=(const Vector2 &other);
    Vector2 &operator/=(const Vector2 &other);
    Vector2 &operator*=(float scalar);
    Vector2 &operator/=(float scalar);

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator*(const Vector2 &other) const;
    Vector2 operator/(const Vector2 &other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    bool operator==(const Vector2 &other) const;
    bool operator!=(const Vector2 &other) const;

    //Cast operator
    operator Vector2Int() const;

    //Additional methods
    float Cross(const Vector2 &other) const;
    Vector2 Abs() const;
    float Dot(const Vector2 &other) const;
    float Magnitude() const;
    Vector2 Normalize() const;
    Vector2 Forward() const;
    Vector2 Right() const;
    Vector2 Up() const;
};

#endif // VECTOR2_HPP