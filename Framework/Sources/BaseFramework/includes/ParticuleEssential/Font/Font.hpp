#ifndef FONT_HPP
#define FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>

namespace Particule::Essential
{
    //Abstract class
    class Font
    {
    public:
        static Font* currentFont;

        Font();
        Font(const char* path, int size) {
            (void)path;
            (void)size;
        };
        ~Font();
        virtual void SetSize(int size) {
            (void)size;
        };
        virtual int GetSize(){
            return 0;
        };
        virtual void DrawText(const char* text, int x, int y) {
            (void)text;
            (void)x;
            (void)y;
        };
        virtual void DrawTextColor(const char* text, int x, int y, Color color) {
            (void)text;
            (void)x;
            (void)y;
            (void)color;
        };
        virtual Vector2Int GetTextSize(const char* text) {
            (void)text;
            return {0,0};
        };
    };
}

#endif // FONT_HPP