#ifndef INTERNAL_FONT_HPP
#define INTERNAL_FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>

namespace Particule::Essential
{
    class InternalFont
    {
    public:
        InternalFont();
        InternalFont(const char* path, int size);
        ~InternalFont();
        void SetSize(int size);
        int GetSize();
        void DrawText(const char* text, int x, int y);
        void DrawTextColor(const char* text, int x, int y, Color color);
        Vector2Int GetTextSize(const char* text);
    };
}

#endif // INTERNAL_FONT_HPP