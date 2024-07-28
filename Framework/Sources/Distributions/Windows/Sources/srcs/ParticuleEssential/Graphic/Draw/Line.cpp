#include <ParticuleEssential/Graphic/Draw/Line.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <SDL2/SDL.h>

namespace Particule::Essential
{
    void DrawLine(int x1, int y1, int x2, int y2, Color color)
    {
        SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(window->renderer, x1, y1, x2, y2);
    }
}