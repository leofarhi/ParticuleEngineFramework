#ifndef DRAW_RECT_HPP
#define DRAW_RECT_HPP
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/System/gint.hpp>

namespace Particule::Api
{

    inline void DrawRect(int x, int y, int w, int h, const Color& color)
    {
        if (w <= 0 || h <= 0)
            return;
        w--;
        h--;
        gint::dline(x, y, x + w, y, color.Raw());
        gint::dline(x, y, x, y + h, color.Raw());
        gint::dline(x + w, y, x + w, y + h, color.Raw());
        gint::dline(x, y + h, x + w, y + h, color.Raw());
    }

    inline void DrawRectFill(int x, int y, int w, int h, const Color& color)
    {
        if (w <= 0 || h <= 0)
            return;
        gint::drect(x, y, w-1, h-1, color.Raw());
    }
}

#endif // DRAW_RECT_HPP