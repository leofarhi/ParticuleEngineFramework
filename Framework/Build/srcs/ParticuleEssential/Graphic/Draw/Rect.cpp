#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include "../../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <SDL2/SDL.h>

namespace Particule::Essential::Graphic::Draw
{
    void DrawRect(int x, int y, int w, int h, Color color)
    {
        SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderDrawRect(window->renderer, &rect);
    }

    void DrawRectFill(int x, int y, int w, int h, Color color)
    {
        SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderFillRect(window->renderer, &rect);
    }
}