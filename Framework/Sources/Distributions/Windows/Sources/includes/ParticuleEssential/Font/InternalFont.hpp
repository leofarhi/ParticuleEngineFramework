#ifndef INTERNAL_FONT_HPP
#define INTERNAL_FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Font/Font.hpp>
#include <SDL2/SDL_ttf.h>

namespace Particule::Essential
{
    class InternalFont
    {
    private:
        char* path;
        TTF_Font* font;
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