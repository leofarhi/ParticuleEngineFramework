#ifndef COLOR_HPP
#define COLOR_HPP

namespace Particule::Api
{
    typedef unsigned long long int ColorRaw;
    
    class Color
    {
        public:
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
            Color(ColorRaw raw);
            Color(const Color &other);
            Color &operator=(const Color &other);
            ~Color();

            void SetR(unsigned char r);
            void SetG(unsigned char g);
            void SetB(unsigned char b);
            void SetA(unsigned char a);

            unsigned char R() const;
            unsigned char G() const;
            unsigned char B() const;
            unsigned char A() const;

            ColorRaw Raw() const;
            static ColorRaw MultiplyColorRaw(ColorRaw a, ColorRaw b);
            
            void Get(unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) const;

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