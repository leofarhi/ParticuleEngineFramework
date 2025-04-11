#ifndef DRAW_PIXEL_HPP
#define DRAW_PIXEL_HPP
#include <ParticuleApi/Graphics/Color.hpp>

namespace Particule::Api
{
    void DrawPixel(int x, int y, const Color& color);

    //Draws a pixel without checking if the coordinates are in the screen
    void DrawPixelUnsafe(int x, int y, const Color& color);
}

#endif // DRAW_PIXEL_HPP