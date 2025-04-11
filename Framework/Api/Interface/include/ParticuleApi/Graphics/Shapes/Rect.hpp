#ifndef DRAW_RECT_HPP
#define DRAW_RECT_HPP
#include <ParticuleApi/Graphics/Color.hpp>

namespace Particule::Api
{
    void DrawRect(int x, int y, int w, int h, const Color& color);

    void DrawRectFill(int x, int y, int w, int h, const Color& color);
}

#endif // DRAW_RECT_HPP