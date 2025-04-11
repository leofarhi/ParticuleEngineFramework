#ifndef DRAW_LINE_HPP
#define DRAW_LINE_HPP
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/System/sdl2.hpp>
#include <ParticuleApi/System/App.hpp>

namespace Particule::Api
{
    
    inline void DrawLine(int x1, int y1, int x2, int y2, const Color& color)
    {
        sdl2::SDL_SetRenderDrawColor(App::DrawWindow->renderer, color.R(), color.G(), color.B(), color.A());
        sdl2::SDL_RenderDrawLine(App::DrawWindow->renderer, x1, y1, x2, y2);
    }
}

#endif // DRAW_LINE_HPP