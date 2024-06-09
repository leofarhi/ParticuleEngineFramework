#include <ParticuleEssential/Graphic/Color.hpp>

namespace Particule::Essential
{
    Color::Color()
    {
        r = 0;
        g = 0;
        b = 0;
        a = 255;
    }

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color(long long int raw)
    {
        //raw = 0xRRGGBBAA
        r = (raw >> 24) & 0xFF;
        g = (raw >> 16) & 0xFF;
        b = (raw >> 8) & 0xFF;
        a = raw & 0xFF;
    }

    Color::Color(const Color &color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }

    Color &Color::operator=(const Color &color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
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