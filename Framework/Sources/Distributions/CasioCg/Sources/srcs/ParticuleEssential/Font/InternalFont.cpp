#include "../../../includes/ParticuleEssential/Font/InternalFont.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <string.h>

namespace Particule::Essential
{
    InternalFont::InternalFont()
    {
        char* path = nullptr;
        font = nullptr;
        size = 0;
    }

    InternalFont::InternalFont(const char* path, int size)
    {
        this->path = new char[strlen(path) + 1];
        strcpy(this->path, path);
        this->size = size;
        font = nullptr;
    }

    InternalFont::~InternalFont()
    {
        if (path != nullptr)
            delete[] path;
    }

    void InternalFont::SetSize(int size)
    {
        this->size = size;
    }

    int InternalFont::GetSize()
    {
        return size;
    }

    void InternalFont::DrawText(const char* text, int x, int y)
    {
        DrawTextColor(text, x, y, COLOR_WHITE);
    }

    void InternalFont::DrawTextColor(const char* text, int x, int y, Color color)
    {
        if (font != NULL)
            dfont(font);
        else
            dfont(dfont_default());
        dtext(x, y, color.color, text);
    }

    Vector2Int InternalFont::GetTextSize(const char* text)
    {
        Vector2Int size = {0,0};
        if (font == NULL)
            dsize(text,dfont_default(), &size.x, &size.y);
        else
            dsize(text,this->font, &size.x, &size.y);
        return size;
    }
}