#include "../../../includes/ParticuleEssential/Font/Font.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <string.h>

namespace Particule::Essential
{
    Font::Font()
    {
        char* path = nullptr;
        font = nullptr;
        size = 0;
    }

    Font::Font(const char* path, int size)
    {
        this->path = new char[strlen(path) + 1];
        strcpy(this->path, path);
        this->size = size;
        font = nullptr;
    }

    Font::~Font()
    {
        if (path != nullptr)
            delete[] path;
    }

    void Font::SetSize(int size)
    {
        this->size = size;
    }

    int Font::GetSize()
    {
        return size;
    }

    void Font::DrawText(const char* text, int x, int y)
    {
        DrawTextColor(text, x, y, COLOR_WHITE);
    }

    void Font::DrawTextColor(const char* text, int x, int y, Color color)
    {
        if (font != NULL)
            dfont(font);
        else
            dfont(dfont_default());
        dtext(x, y, color.color, text);
    }

    Vector2Int Font::GetTextSize(const char* text)
    {
        Vector2Int size = {0,0};
        if (font == NULL)
            dsize(text,dfont_default(), &size.x, &size.y);
        else
            dsize(text,this->font, &size.x, &size.y);
        return size;
    }
}