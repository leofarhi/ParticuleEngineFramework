#ifndef PE_FIXEDPOINT_HPP
#define PE_FIXEDPOINT_HPP

class FixedPoint
{
private:
    int value;
public:
    FixedPoint();
    FixedPoint(int value);
    FixedPoint(float value);
    FixedPoint(double value);
    FixedPoint(const FixedPoint& other);
    ~FixedPoint();

    FixedPoint& operator=(const FixedPoint& other);
    FixedPoint& operator=(int value);
    FixedPoint& operator=(float value);

    FixedPoint operator+(const FixedPoint& other) const;
    FixedPoint operator-(const FixedPoint& other) const;
    FixedPoint operator*(const FixedPoint& other) const;
    FixedPoint operator/(const FixedPoint& other) const;

    FixedPoint operator+(int value) const;
    FixedPoint operator-(int value) const;
    FixedPoint operator*(int value) const;
    FixedPoint operator/(int value) const;

    FixedPoint operator+(float value) const;
    FixedPoint operator-(float value) const;
    FixedPoint operator*(float value) const;
    FixedPoint operator/(float value) const;

    FixedPoint& operator+=(const FixedPoint& other);
    FixedPoint& operator-=(const FixedPoint& other);
    FixedPoint& operator*=(const FixedPoint& other);
    FixedPoint& operator/=(const FixedPoint& other);

    FixedPoint& operator+=(int value);
    FixedPoint& operator-=(int value);
    FixedPoint& operator*=(int value);
    FixedPoint& operator/=(int value);

    FixedPoint& operator+=(float value);
    FixedPoint& operator-=(float value);
    FixedPoint& operator*=(float value);
    FixedPoint& operator/=(float value);


    bool operator==(const FixedPoint& other) const;
    bool operator!=(const FixedPoint& other) const;
    bool operator<(const FixedPoint& other) const;
    bool operator>(const FixedPoint& other) const;
    bool operator<=(const FixedPoint& other) const;
    bool operator>=(const FixedPoint& other) const;

    bool operator==(int value) const;
    bool operator!=(int value) const;
    bool operator<(int value) const;
    bool operator>(int value) const;
    bool operator<=(int value) const;
    bool operator>=(int value) const;

    bool operator==(float value) const;
    bool operator!=(float value) const;
    bool operator<(float value) const;
    bool operator>(float value) const;
    bool operator<=(float value) const;
    bool operator>=(float value) const;

    operator int() const;
    operator float() const;
};

#endif // PE_FIXEDPOINT_HPP