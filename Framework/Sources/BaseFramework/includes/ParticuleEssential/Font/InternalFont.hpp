#ifndef INTERNAL_FONT_HPP
#define INTERNAL_FONT_HPP
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Font/Font.hpp>

namespace Particule::Essential
{
    class InternalFont : public Font
    {
    public:
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