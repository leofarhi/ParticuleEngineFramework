#include <ParticuleEssential/Types/FixedPoint.hpp>


FixedPoint::FixedPoint() : value(0){}

FixedPoint::FixedPoint(int value) : value(value << 16){}

FixedPoint::FixedPoint(float value) : value((int)(value * 65536)){}

FixedPoint::FixedPoint(const FixedPoint& other) : value(other.value){}

FixedPoint::~FixedPoint(){}

FixedPoint& FixedPoint::operator=(const FixedPoint& other)
{
    this->value = other.value;
    return *this;
}

FixedPoint& FixedPoint::operator=(int value)
{
    this->value = value << 16;
    return *this;
}

FixedPoint& FixedPoint::operator=(float value)
{
    this->value = (int)(value * 65536);
    return *this;
}

FixedPoint FixedPoint::operator+(const FixedPoint& other) const
{
    return FixedPoint(this->value + other.value);
}

FixedPoint FixedPoint::operator-(const FixedPoint& other) const
{
    return FixedPoint(this->value - other.value);
}

FixedPoint FixedPoint::operator*(const FixedPoint& other) const
{
    return FixedPoint((this->value * other.value) >> 16);
}

FixedPoint FixedPoint::operator/(const FixedPoint& other) const
{
    return FixedPoint((this->value << 16) / other.value);
}

FixedPoint FixedPoint::operator+(int value) const
{
    return FixedPoint(this->value + (value << 16));
}

FixedPoint FixedPoint::operator-(int value) const
{
    return FixedPoint(this->value - (value << 16));
}

FixedPoint FixedPoint::operator*(int value) const
{
    return FixedPoint(this->value * value);
}

FixedPoint FixedPoint::operator/(int value) const
{
    return FixedPoint(this->value / value);
}

FixedPoint FixedPoint::operator+(float value) const
{
    return FixedPoint(this->value + (int)(value * 65536));
}

FixedPoint FixedPoint::operator-(float value) const
{
    return FixedPoint(this->value - (int)(value * 65536));
}

FixedPoint FixedPoint::operator*(float value) const
{
    return FixedPoint((this->value * (int)(value * 65536)) >> 16);
}

FixedPoint FixedPoint::operator/(float value) const
{
    return FixedPoint((this->value << 16) / (int)(value * 65536));
}

FixedPoint& FixedPoint::operator+=(const FixedPoint& other)
{
    this->value += other.value;
    return *this;
}

FixedPoint& FixedPoint::operator-=(const FixedPoint& other)
{
    this->value -= other.value;
    return *this;
}

FixedPoint& FixedPoint::operator*=(const FixedPoint& other)
{
    this->value = (this->value * other.value) >> 16;
    return *this;
}

FixedPoint& FixedPoint::operator/=(const FixedPoint& other)
{
    this->value = (this->value << 16) / other.value;
    return *this;
}

FixedPoint& FixedPoint::operator+=(int value)
{
    this->value += value << 16;
    return *this;
}

FixedPoint& FixedPoint::operator-=(int value)
{
    this->value -= value << 16;
    return *this;
}

FixedPoint& FixedPoint::operator*=(int value)
{
    this->value *= value;
    return *this;
}

FixedPoint& FixedPoint::operator/=(int value)
{
    this->value /= value;
    return *this;
}

FixedPoint& FixedPoint::operator+=(float value)
{
    this->value += (int)(value * 65536);
    return *this;
}

FixedPoint& FixedPoint::operator-=(float value)
{
    this->value -= (int)(value * 65536);
    return *this;
}

FixedPoint& FixedPoint::operator*=(float value)
{
    this->value = (this->value * (int)(value * 65536)) >> 16;
    return *this;
}

FixedPoint& FixedPoint::operator/=(float value)
{
    this->value = (this->value << 16) / (int)(value * 65536);
    return *this;
}

bool FixedPoint::operator==(const FixedPoint& other) const
{
    return this->value == other.value;
}

bool FixedPoint::operator!=(const FixedPoint& other) const
{
    return this->value != other.value;
}

bool FixedPoint::operator<(const FixedPoint& other) const
{
    return this->value < other.value;
}

bool FixedPoint::operator>(const FixedPoint& other) const
{
    return this->value > other.value;
}

bool FixedPoint::operator<=(const FixedPoint& other) const
{
    return this->value <= other.value;
}

bool FixedPoint::operator>=(const FixedPoint& other) const
{
    return this->value >= other.value;
}

bool FixedPoint::operator==(int value) const
{
    return this->value == value << 16;
}

bool FixedPoint::operator!=(int value) const
{
    return this->value != value << 16;
}

bool FixedPoint::operator<(int value) const
{
    return this->value < value << 16;
}

bool FixedPoint::operator>(int value) const
{
    return this->value > value << 16;
}

bool FixedPoint::operator<=(int value) const
{
    return this->value <= value << 16;
}

bool FixedPoint::operator>=(int value) const
{
    return this->value >= value << 16;
}

bool FixedPoint::operator==(float value) const
{
    return this->value == (int)(value * 65536);
}

bool FixedPoint::operator!=(float value) const
{
    return this->value != (int)(value * 65536);
}

bool FixedPoint::operator<(float value) const
{
    return this->value < (int)(value * 65536);
}

bool FixedPoint::operator>(float value) const
{
    return this->value > (int)(value * 65536);
}

bool FixedPoint::operator<=(float value) const
{
    return this->value <= (int)(value * 65536);
}

bool FixedPoint::operator>=(float value) const
{
    return this->value >= (int)(value * 65536);
}

FixedPoint::operator int() const
{
    return this->value >> 16;
}

FixedPoint::operator float() const
{
    return (float)this->value / 65536;
}

