#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <gint/gint.h>
#include <gint/display.h>

namespace Particule::Essential
{
    void DrawRect(int x, int y, int w, int h, Color color)
    {
        if (w <= 0 || h <= 0)
            return;
        w--;
        h--;
        dline(x, y, x + w, y, color.color);
        dline(x + w, y, x + w, y + h, color.color);
        dline(x, y + h, x, y, color.color);
        dline(x, y + h, x + w, y + h, color.color);
    }

    void DrawRectFill(int x, int y, int w, int h, Color color)
    {
        if (w <= 0 || h <= 0)
            return;
        w--;
        h--;
        drect(x, y, x + w, y + h, color.color);
    }
}