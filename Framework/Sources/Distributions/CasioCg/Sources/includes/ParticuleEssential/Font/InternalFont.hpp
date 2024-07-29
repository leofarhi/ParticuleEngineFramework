#ifndef INTERNAL_FONT_HPP
#define INTERNAL_FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Font/Font.hpp>
#include <gint/gint.h>
#include <gint/display.h>
#include <gint/keyboard.h>

namespace Particule::Essential
{
    class InternalFont : public Font
    {
    private:
        char* path;
        font_t* font;
        int size;
    public:
        static InternalFont* currentFont;

        InternalFont();
        InternalFont(const char* path, int size);
        ~InternalFont();
        void SetSize(int size) override;
        int GetSize() override;
        void DrawText(const char* text, int x, int y) override;
        void DrawTextColor(const char* text, int x, int y, Color color) override;
        Vector2Int GetTextSize(const char* text) override;
    };
}

#endif // INTERNAL_FONT_HPP