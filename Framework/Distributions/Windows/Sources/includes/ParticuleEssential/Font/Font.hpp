#ifndef FONT_HPP
#define FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <SDL2/SDL_ttf.h>

namespace Particule::Essential
{
    class Font
    {
    private:
        char* path;
        TTF_Font* font;
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