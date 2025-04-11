#ifndef DRAW_PIXEL_HPP
#define DRAW_PIXEL_HPP
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/System/gint.hpp>

namespace Particule::Api
{
    inline void DrawPixel(int x, int y, const Color& color)
    {
        gint::dpixel(x, y, color.Raw());
    }

    //Draws a pixel without checking if the coordinates are in the screen
    inline void DrawPixelUnsafe(int x, int y, const Color& color)
    {
        gint::gint_vram[DWIDTH * y + x] = color.Raw();
    }
}

#endif // DRAW_PIXEL_HPP