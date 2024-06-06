#ifndef COLOR_HPP
#define COLOR_HPP

namespace Particule::Essential::Graphic
{
    struct Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        Color();
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        Color(unsigned int hex);
        Color(const Color &other);
        Color &operator=(const Color &other);
        bool operator==(const Color &other) const;
        bool operator!=(const Color &other) const;
    };

    #define COLOR_BLACK Color(0, 0, 0, 255)
    #define COLOR_WHITE Color(255, 255, 255, 255)
    #define COLOR_RED Color(255, 0, 0, 255)
    #define COLOR_GREEN Color(0, 255, 0, 255)
    #define COLOR_BLUE Color(0, 0, 255, 255)
    #define COLOR_YELLOW Color(255, 255, 0, 255)
    #define COLOR_CYAN Color(0, 255, 255, 255)
    #define COLOR_MAGENTA Color(255, 0, 255, 255)
}
#endif // COLOR_HPP