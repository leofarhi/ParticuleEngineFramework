#ifndef FONT_HPP
#define FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>

namespace Particule::Essential::Font
{
    using Particule::Essential::Graphic::Color;
    class Font
    {
    public:
        Font();
        Font(const char* path, int size);
        ~Font();
        void SetSize(int size);
        int GetSize();
        void DrawText(const char* text, int x, int y);
        void DrawTextColor(const char* text, int x, int y, Color color);
        Vector2Int GetTextSize(const char* text);
    };

    extern Font* mainFont;
}

#endif // FONT_HPP