#include "../../../includes/ParticuleEssential/Font/Font.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <string.h>

namespace Particule::Essential
{
    Font::Font()
    {
        char* path = nullptr;
        font = nullptr;
    }

    Font::Font(const char* path, int size)
    {
        font = TTF_OpenFont(path, size);
        this->path = new char[strlen(path) + 1];
        strcpy(this->path, path);
        if (font == nullptr)
            error_exit(1, "Failed to load font: %s\n", path);
    }

    Font::~Font()
    {
        if (font != nullptr)
            TTF_CloseFont(font);
        if (path != nullptr)
            delete[] path;
    }

    void Font::SetSize(int size)
    {
        if (path == nullptr)
            return;
        if (font != nullptr)
            TTF_CloseFont(font);
        font = TTF_OpenFont(path, size);
        if (font == nullptr)
            error_exit(1, "Failed to load font: %s\n", path);
    }

    int Font::GetSize()
    {
        return TTF_FontHeight(font);
    }

    void Font::DrawText(const char* text, int x, int y)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, {255, 255, 255, 255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);
        SDL_Rect rect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(window->renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void Font::DrawTextColor(const char* text, int x, int y, Color color)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, {color.r, color.g, color.b, color.a});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);
        SDL_Rect rect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(window->renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    Vector2Int Font::GetTextSize(const char* text)
    {
        int w, h;
        TTF_SizeText(font, text, &w, &h);
        return {w, h};
    }
}