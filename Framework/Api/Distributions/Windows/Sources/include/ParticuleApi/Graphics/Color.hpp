#ifndef COLOR_HPP
#define COLOR_HPP
#include <cstdint>

namespace Particule::Api
{
    typedef uint32_t ColorRaw;
    
    class Color
    {
    private:
        unsigned char r, g, b, a;
        ColorRaw color;
    
        static constexpr ColorRaw Pack(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            //raw = 0xRRGGBBAA
            return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3) | ((a & 0xFF) << 24);
        }
    
    public:
        // Constructeurs
        constexpr Color() : r(0), g(0), b(0), a(0), color(0) {}
    
        constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
            : r(r), g(g), b(b), a(a), color(Pack(r, g, b, a)) {}
    
        constexpr Color(ColorRaw raw)
            : r((raw >> 8) & 0xF8), g((raw >> 3) & 0xFC), b((raw << 3) & 0xF8), a((raw >> 24) & 0xFF), color(raw) {}
    
        constexpr Color(const Color& other)
            : r(other.r), g(other.g), b(other.b), a(other.a), color(other.color) {}
    
        // Assignation
        constexpr Color& operator=(const Color& other) {
            r = other.r; g = other.g; b = other.b; a = other.a; color = other.color;
            return *this;
        }
    
        // Accesseurs inline
        constexpr unsigned char R() const { return r; }
        constexpr unsigned char G() const { return g; }
        constexpr unsigned char B() const { return b; }
        constexpr unsigned char A() const { return a; }
        constexpr ColorRaw Raw() const { return color; }

        static inline ColorRaw MultiplyColorRaw(ColorRaw a, ColorRaw b)
        {
            (void)a; (void)b;
            return 0;
        }
    
        constexpr void Get(unsigned char& outR, unsigned char& outG, unsigned char& outB, unsigned char& outA) const {
            outR = r; outG = g; outB = b; outA = a;
        }
    
        // Mutateurs inline
        inline void SetR(unsigned char red)   { r = red; color = Pack(r, g, b, a); }
        inline void SetG(unsigned char green) { g = green; color = Pack(r, g, b, a); }
        inline void SetB(unsigned char blue)  { b = blue; color = Pack(r, g, b, a); }
        inline void SetA(unsigned char alpha) { a = alpha; }
    
        // Opérateurs de comparaison
        constexpr bool operator==(const Color& other) const {
            return color == other.color && a == other.a;
        }
    
        constexpr bool operator!=(const Color& other) const {
            return !(*this == other);
        }
    
        // Destructeur trivial
        ~Color() = default;
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