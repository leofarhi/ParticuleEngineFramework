#ifndef DRAW_PIXEL_HPP
#define DRAW_PIXEL_HPP
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/System/sdl2.hpp>
#include <ParticuleApi/System/App.hpp>

namespace Particule::Api
{
    inline void DrawPixel(int x, int y, const Color& color)
    {
        sdl2::SDL_SetRenderDrawColor(App::DrawWindow->renderer, color.R(), color.G(), color.B(), color.A());
        sdl2::SDL_RenderDrawPoint(App::DrawWindow->renderer, x, y);
    }

    //Draws a pixel without checking if the coordinates are in the screen
    inline void DrawPixelUnsafe(int x, int y, const Color& color)
    {
        sdl2::SDL_SetRenderDrawColor(App::DrawWindow->renderer, color.R(), color.G(), color.B(), color.A());
        sdl2::SDL_RenderDrawPoint(App::DrawWindow->renderer, x, y);
    }
}

#endif // DRAW_PIXEL_HPP