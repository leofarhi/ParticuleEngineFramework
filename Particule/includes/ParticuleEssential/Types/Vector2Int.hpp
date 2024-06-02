#ifndef VECTOR2INT_HPP
#define VECTOR2INT_HPP

class Vector2Int
{
public:
    int x;
    int y;

    Vector2Int();
    Vector2Int(int x, int y);
    ~Vector2Int();

    Vector2Int &operator=(const Vector2Int &other);
    Vector2Int &operator+=(const Vector2Int &other);
    Vector2Int &operator-=(const Vector2Int &other);
    Vector2Int &operator*=(int scalar);
    Vector2Int &operator/=(int scalar);

    Vector2Int operator+(const Vector2Int &other) const;
    Vector2Int operator-(const Vector2Int &other) const;
    Vector2Int operator*(int scalar) const;
    Vector2Int operator/(int scalar) const;
    bool operator==(const Vector2Int &other) const;
    bool operator!=(const Vector2Int &other) const;
};

#endif // VECTOR2INT_HPP