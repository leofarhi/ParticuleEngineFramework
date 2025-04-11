#ifndef DRAW_LINE_HPP
#define DRAW_LINE_HPP
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/System/gint.hpp>

namespace Particule::Api
{
    
    inline void DrawLine(int x1, int y1, int x2, int y2, const Color& color) {
        gint::dline(x1, y1, x2, y2, color.Raw());
    }
}

#endif // DRAW_LINE_HPP