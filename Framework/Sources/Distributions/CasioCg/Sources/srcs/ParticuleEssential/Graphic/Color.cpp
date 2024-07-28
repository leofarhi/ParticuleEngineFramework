#include <ParticuleEssential/Graphic/Color.hpp>

namespace Particule::Essential
{
    Color::Color()
    {
        r = 0;
        g = 0;
        b = 0;
        a = 255;
        color = 0;
    }

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
        this->color = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3);
    }

    Color::Color(long long int raw)
    {
        this->color = raw;
        this->r = ((raw >> 11) & 0b11111) << 3;
        this->g = ((raw >> 5) & 0b111111) << 2;
        this->b = (raw & 0b11111) << 3;
        this->a = 255;
    }

    Color::Color(const Color &color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
        this->color = color.color;
    }

    Color &Color::operator=(const Color &color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
        this->color = color.color;
        return *this;
    }

    bool Color::operator==(const Color &color) const
    {
        return r == color.r && g == color.g && b == color.b && a == color.a;
    }

    bool Color::operator!=(const Color &color) const
    {
        return r != color.r || g != color.g || b != color.b || a != color.a;
    }

} // namespace Particule::Essential::Graphic