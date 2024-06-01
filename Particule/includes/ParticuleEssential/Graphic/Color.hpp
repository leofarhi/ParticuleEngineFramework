#ifndef COLOR_HPP
#define COLOR_HPP

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Color();
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    Color(const Color &other);
    Color &operator=(const Color &other);
    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;
};

#endif // COLOR_HPP