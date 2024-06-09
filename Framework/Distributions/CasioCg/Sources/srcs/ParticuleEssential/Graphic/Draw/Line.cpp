#include <ParticuleEssential/Graphic/Draw/Line.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <gint/gint.h>
#include <gint/display.h>

namespace Particule::Essential
{
    void DrawLine(int x1, int y1, int x2, int y2, Color color)
    {
        dline(x1, y1, x2, y2, color.color);
    }
}