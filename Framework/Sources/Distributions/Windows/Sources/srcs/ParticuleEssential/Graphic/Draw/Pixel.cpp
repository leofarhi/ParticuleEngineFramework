#include <ParticuleEssential/Graphic/Draw/Pixel.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <SDL2/SDL.h>

namespace Particule::Essential
{
    void DrawPixel(int x, int y, Color color)
    {
        SDL_SetRenderDrawColor(Window::DrawingWindow->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(Window::DrawingWindow->renderer, x, y);
    }

    void DrawPixelUnsafe(int x, int y, Color color)
    {
        SDL_SetRenderDrawColor(Window::DrawingWindow->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(Window::DrawingWindow->renderer, x, y);
    }
}