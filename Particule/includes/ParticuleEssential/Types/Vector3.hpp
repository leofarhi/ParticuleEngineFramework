#ifndef VECTOR3_HPP
#define VECTOR3_HPP

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);
    ~Vector3();

    Vector3 &operator=(const Vector3 &other);
    Vector3 &operator+=(const Vector3 &other);
    Vector3 &operator-=(const Vector3 &other);
    Vector3 &operator*=(float scalar);
    Vector3 &operator/=(float scalar);

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;
    bool operator==(const Vector3 &other) const;
    bool operator!=(const Vector3 &other) const;
};

#endif // VECTOR3_HPP