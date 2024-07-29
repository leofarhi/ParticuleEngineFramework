#include "../../../includes/ParticuleEssential/Texture/Texture.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Particule::Essential
{

    Texture::Texture()
    {
        texture = nullptr;
        surface = nullptr;
        width = 0;
        height = 0;
    }

    Texture::~Texture()
    {
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
        }
    }

    int Texture::Width()
    {
        return width;
    }

    int Texture::Height()
    {
        return height;
    }

    bool Texture::IsWritable()
    {
        return surface != nullptr;
    }

    void Texture::Draw(int x, int y)
    {
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderCopy(Window::DrawingWindow->renderer, texture, nullptr, &rect);
    }

    void Texture::DrawSub(int x, int y, Rect rect)
    {
        SDL_Rect dst = {x, y, rect.w, rect.h};
        SDL_Rect src = {rect.x, rect.y, rect.w, rect.h};
        SDL_RenderCopy(Window::DrawingWindow->renderer, texture, &src, &dst);
    }

    void Texture::DrawSize(int x, int y, int w, int h)
    {
        if (w < 0 || h < 0)
        {
            DrawSubSize(x, y, w, h, {0, 0, width, height});
        }
        else
        {
            SDL_Rect rect = {x, y, w, h};
            SDL_RenderCopy(Window::DrawingWindow->renderer, texture, nullptr, &rect);
        }
    }

    void Texture::DrawSubSize(int x, int y, int w, int h, Rect rect)
    {
        if (rect.w == w && rect.h == h)
        {
            DrawSub(x, y, rect);
            return;
        }
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (w < 0)
            flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
        if (h < 0)
            flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
        w = abs(w);
        h = abs(h);
        if (rect.x + rect.w > width && w > 0)
        {
            float ratio = (float)w / rect.w;
            rect.w = width - rect.x;
            w = rect.w * ratio;
        }
        if (rect.y + rect.h > height && h > 0)
        {
            float ratio = (float)h / rect.h;
            rect.h = height - rect.y;
            h = rect.h * ratio;
        }
        SDL_Rect dst = {x, y, w, h};
        SDL_Rect src = {rect.x, rect.y, rect.w, rect.h};
        SDL_RenderCopyEx(Window::DrawingWindow->renderer, texture, &src, &dst, 0, nullptr, flip);
    }

    void Texture::DrawColor(int x, int y, Color color)
    {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
        Draw(x, y);
        SDL_SetTextureColorMod(texture, 255, 255, 255);
        SDL_SetTextureAlphaMod(texture, 255);
    }

    void Texture::DrawSubColor(int x, int y, Rect rect, Color color)
    {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
        DrawSub(x, y, rect);
        SDL_SetTextureColorMod(texture, 255, 255, 255);
        SDL_SetTextureAlphaMod(texture, 255);
    }

    void Texture::DrawSizeColor(int x, int y, int w, int h, Color color)
    {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
        DrawSize(x, y, w, h);
        SDL_SetTextureColorMod(texture, 255, 255, 255);
        SDL_SetTextureAlphaMod(texture, 255);
    }

    void Texture::DrawSubSizeColor(int x, int y, int w, int h, Rect rect, Color color)
    {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
        DrawSubSize(x, y, w, h, rect);
        SDL_SetTextureColorMod(texture, 255, 255, 255);
        SDL_SetTextureAlphaMod(texture, 255);
    }

    void Texture::WritePixel(int x, int y, Color color)
    {
        Uint32* pixels = (Uint32*)surface->pixels;
        pixels[y * width + x] = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
    }

    void Texture::WritePixelInt(int x, int y, long long color)
    {
        Uint32* pixels = (Uint32*)surface->pixels;
        pixels[y * width + x] = color;
    }

    Color Texture::ReadPixel(int x, int y)
    {
        Uint32* pixels = (Uint32*)surface->pixels;
        Uint32 pixel = pixels[y * width + x];
        Color color;
        SDL_GetRGBA(pixel, surface->format, &color.r, &color.g, &color.b, &color.a);
        return color;
    }

    long long Texture::ReadPixelInt(int x, int y)
    {
        Uint32* pixels = (Uint32*)surface->pixels;
        return pixels[y * width + x];
    }

    void Texture::SetPixel(int x, int y, Color color)
    {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return;
        WritePixel(x, y, color);
    }

    Color Texture::GetPixel(int x, int y)
    {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return {0, 0, 0, 0};
        return ReadPixel(x, y);
    }

    Texture* Texture::Load(const char* path)
    {
        Texture* texture = new Texture();
        SDL_Surface* surface = IMG_Load(path);
        if (surface == nullptr)
            error_exit(1, "Can't load texture %s\n", path);
        texture->texture = SDL_CreateTextureFromSurface(Window::DrawingWindow->renderer, surface);
        if (texture->texture == nullptr)
            error_exit(1, "Can't create texture from surface %s\n", path);
        texture->width = surface->w;
        texture->height = surface->h;
        texture->surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
        SDL_FreeSurface(surface);
        return texture;
    }

    Texture* Texture::Create(int width, int height)
    {
        Texture* texture = new Texture();
        texture->texture = SDL_CreateTexture(Window::DrawingWindow->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
        if (texture->texture == nullptr)
            error_exit(1, "Can't create texture\n");
        texture->width = width;
        texture->height = height;
        texture->surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        return texture;
    }

    Sprite* Texture::CreateSprite(Texture* texture, Rect rect)
    {
        return new Sprite(texture, rect);
    }

}