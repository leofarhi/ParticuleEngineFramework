#ifndef VECTOR3INT_HPP
#define VECTOR3INT_HPP

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
    Vector3Int &operator*=(int scalar);
    Vector3Int &operator/=(int scalar);

    Vector3Int operator+(const Vector3Int &other) const;
    Vector3Int operator-(const Vector3Int &other) const;
    Vector3Int operator*(int scalar) const;
    Vector3Int operator/(int scalar) const;
    bool operator==(const Vector3Int &other) const;
    bool operator!=(const Vector3Int &other) const;
};

#endif // VECTOR3INT_HPP