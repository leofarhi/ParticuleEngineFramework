#include <ParticuleEssential/Graphic/Draw/Pixel.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <SDL2/SDL.h>

namespace Particule::Essential::Graphic::Draw
{
    void DrawPixel(int x, int y, Color color)
    {
        SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(window->renderer, x, y);
    }

    void DrawPixelUnsafe(int x, int y, Color color)
    {
        SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(window->renderer, x, y);
    }
}