#ifndef VECTOR2_HPP
#define VECTOR2_HPP

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
    Vector2 &operator*=(float scalar);
    Vector2 &operator/=(float scalar);

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    bool operator==(const Vector2 &other) const;
    bool operator!=(const Vector2 &other) const;
};

#endif // VECTOR2_HPP