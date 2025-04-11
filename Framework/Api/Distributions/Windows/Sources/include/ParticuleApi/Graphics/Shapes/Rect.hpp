#ifndef DRAW_RECT_HPP
#define DRAW_RECT_HPP
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/System/sdl2.hpp>
#include <ParticuleApi/System/App.hpp>

namespace Particule::Api
{

    inline void DrawRect(int x, int y, int w, int h, const Color& color)
    {
        sdl2::SDL_SetRenderDrawColor(App::DrawWindow->renderer, color.R(), color.G(), color.B(), color.A());
        sdl2::SDL_Rect rect = { x, y, w, h };
        sdl2::SDL_RenderDrawRect(App::DrawWindow->renderer, &rect);
    }

    inline void DrawRectFill(int x, int y, int w, int h, const Color& color)
    {
        sdl2::SDL_SetRenderDrawColor(App::DrawWindow->renderer, color.R(), color.G(), color.B(), color.A());
        sdl2::SDL_Rect rect = { x, y, w, h };
        sdl2::SDL_RenderFillRect(App::DrawWindow->renderer, &rect);
    }
}

#endif // DRAW_RECT_HPP