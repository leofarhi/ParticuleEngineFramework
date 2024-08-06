#ifndef INTERNAL_FONT_HPP
#define INTERNAL_FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <gint/gint.h>
#include <gint/display.h>
#include <gint/keyboard.h>

namespace Particule::Essential
{
    class InternalFont
    {
    private:
        char* path;
        font_t* font;
        int size;
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