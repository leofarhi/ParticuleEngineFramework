#include "../../../includes/ParticuleEssential/Font/Font.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <string.h>

namespace Particule::Essential::Font
{
    using namespace Particule::Essential::Graphic;
    using Particule::Essential::Graphic::Color;
    Font::Font()
    {
        char* path = nullptr;
        font = nullptr;
    }

    Font::Font(const char* path, int size)
    {
        
    }

    Font::~Font()
    {
        
    }

    void Font::SetSize(int size)
    {
        
    }

    int Font::GetSize()
    {
        
    }

    void Font::DrawText(const char* text, int x, int y)
    {
        
    }

    void Font::DrawTextColor(const char* text, int x, int y, Color color)
    {
        
    }

    Vector2Int Font::GetTextSize(const char* text)
    {
        
    }
}