#include "../../../includes/ParticuleEssential/Font/InternalFont.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <string.h>

namespace Particule::Essential
{
    InternalFont::InternalFont()
    {
        char* path = nullptr;
        font = nullptr;
    }

    InternalFont::InternalFont(const char* path, int size)
    {
        font = TTF_OpenFont(path, size);
        this->path = new char[strlen(path) + 1];
        strcpy(this->path, path);
        if (font == nullptr)
            error_exit(1, "Failed to load font: %s\n", path);
    }

    InternalFont::~InternalFont()
    {
        if (font != nullptr)
            TTF_CloseFont(font);
        if (path != nullptr)
            delete[] path;
    }

    void InternalFont::SetSize(int size)
    {
        if (path == nullptr)
            return;
        if (font != nullptr)
            TTF_CloseFont(font);
        font = TTF_OpenFont(path, size);
        if (font == nullptr)
            error_exit(1, "Failed to load font: %s\n", path);
    }

    int InternalFont::GetSize()
    {
        return TTF_FontHeight(font);
    }

    void InternalFont::DrawText(const char* text, int x, int y)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, {255, 255, 255, 255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::DrawingWindow->renderer, surface);
        SDL_Rect rect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(Window::DrawingWindow->renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void InternalFont::DrawTextColor(const char* text, int x, int y, Color color)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, {color.r, color.g, color.b, color.a});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::DrawingWindow->renderer, surface);
        SDL_Rect rect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(Window::DrawingWindow->renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    Vector2Int InternalFont::GetTextSize(const char* text)
    {
        int w, h;
        TTF_SizeText(font, text, &w, &h);
        return {w, h};
    }
}