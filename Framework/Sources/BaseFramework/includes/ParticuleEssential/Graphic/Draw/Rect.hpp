#ifndef DRAW_RECT_HPP
#define DRAW_RECT_HPP
#include "../Color.hpp"

namespace Particule::Essential
{
    void DrawRect(int x, int y, int w, int h, Color color);

    void DrawRectFill(int x, int y, int w, int h, Color color);
}

#endif // DRAW_RECT_HPP