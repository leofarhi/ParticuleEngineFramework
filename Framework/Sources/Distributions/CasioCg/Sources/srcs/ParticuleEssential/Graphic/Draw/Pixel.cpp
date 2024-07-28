#include <ParticuleEssential/Graphic/Draw/Pixel.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <gint/gint.h>
#include <gint/display.h>

namespace Particule::Essential
{
    void DrawPixel(int x, int y, Color color)
    {
        dpixel(x, y, color.color);
    }

    void DrawPixelUnsafe(int x, int y, Color color)
    {
        gint_vram[DWIDTH * y + x] = color.color;
    }
}