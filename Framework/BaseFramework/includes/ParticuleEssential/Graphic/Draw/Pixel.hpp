#ifndef DRAW_PIXEL_HPP
#define DRAW_PIXEL_HPP
#include "../Color.hpp"

namespace Particule::Essential
{
    void DrawPixel(int x, int y, Color color);

    void DrawPixelUnsafe(int x, int y, Color color);//Draws a pixel without checking if the coordinates are in the screen
}

#endif // DRAW_PIXEL_HPP