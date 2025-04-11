#include <ParticuleApi/Graphics/Image/Texture.hpp>
#include <ParticuleApi/Graphics/Image/Sprite.hpp>
#include <ParticuleApi/System/App.hpp>
#include <ParticuleApi/Types/Fixed.hpp>
#include <ParticuleApi/Types/Vector2.hpp>
#include <algorithm>

namespace Particule::Api
{

    Texture::Texture() : texture(nullptr), surface(nullptr), isWritable(false) {}

    Texture::Texture(const Texture& other) : texture(other.texture), surface(other.surface), isWritable(other.isWritable) {}

    Texture& Texture::operator=(const Texture& other)
    {
        if (this != &other)
        {
            texture = other.texture;
            surface = other.surface;
            isWritable = other.isWritable;
        }
        return *this;
    }

    Texture::~Texture() {
        if (texture != nullptr)
        {
            sdl2::SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        if (surface != nullptr)
        {
            sdl2::SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    void Texture::Draw(int x, int y)
    {
        sdl2::SDL_Rect rect = {x, y, surface->w, surface->h};
        sdl2::SDL_RenderCopy(App::DrawWindow->renderer, texture, nullptr, &rect);
    }

    void Texture::DrawSub(int x, int y, Rect rect)
    {
        //change w and h if the rect is too big
        if (rect.x + rect.w > surface->w) rect.w = surface->w - rect.x;
        if (rect.y + rect.h > surface->h) rect.h = surface->h - rect.y;
        sdl2::SDL_Rect dstRect = {x, y, rect.w, rect.h};
        sdl2::SDL_Rect srcRect = {rect.x, rect.y, rect.w, rect.h};
        sdl2::SDL_RenderCopy(App::DrawWindow->renderer, texture, &srcRect, &dstRect);
    }

    void Texture::DrawSubSize(int x, int y, int w, int h, Rect rect)
    {
        if (rect.w == w && rect.h == h)
        {
            DrawSub(x, y, rect);
            return;
        }
        sdl2::SDL_RendererFlip flip = sdl2::SDL_FLIP_NONE;
        if (w < 0)
            flip = static_cast<sdl2::SDL_RendererFlip>(flip | sdl2::SDL_FLIP_HORIZONTAL);
        if (h < 0)
            flip = static_cast<sdl2::SDL_RendererFlip>(flip | sdl2::SDL_FLIP_VERTICAL);
        w = abs(w);
        h = abs(h);
        //change w and h if the rect is too big
        if (rect.x + rect.w > surface->w) rect.w = surface->w - rect.x;
        if (rect.y + rect.h > surface->h) rect.h = surface->h - rect.y;
        sdl2::SDL_Rect dstRect = {x, y, w, h};
        sdl2::SDL_Rect srcRect = {rect.x, rect.y, rect.w, rect.h};
        sdl2::SDL_RenderCopyEx(App::DrawWindow->renderer, texture, &srcRect, &dstRect, 0, nullptr, flip);
    }

    void Texture::DrawSubSizeColor(int x, int y, int w, int h, Rect rect, const Color& color)
    {
        uint8_t r, g, b, a;
        sdl2::SDL_GetRenderDrawColor(App::DrawWindow->renderer, &r, &g, &b, &a);
        sdl2::SDL_SetTextureColorMod(texture, color.R(), color.G(), color.B());
        sdl2::SDL_SetTextureAlphaMod(texture, color.A());
        DrawSubSize(x, y, w, h, rect);
        sdl2::SDL_SetTextureColorMod(texture, r, g, b);
        sdl2::SDL_SetTextureAlphaMod(texture, a);
    }

    Sprite* Texture::CreateSprite(Rect rect)
    {
        return new Sprite(this, rect);
    }

    Texture* Texture::Load(Resource path)
    {
        Texture* texture = new Texture();
        auto surface = sdl2::IMG_Load(path.c_str());
        texture->surface = sdl2::SDL_ConvertSurfaceFormat(surface, sdl2::SDL_PIXELFORMAT_RGBA32, 0);
        sdl2::SDL_FreeSurface(surface);
        if (texture->surface == nullptr)
        {
            delete texture;
            return nullptr;
        }
        texture->texture = sdl2::SDL_CreateTextureFromSurface(App::DrawWindow->renderer, texture->surface);
        if (texture->texture == nullptr)
        {
            delete texture;
            return nullptr;
        }
        texture->isWritable = false; // Set to true if the texture is writable
        return texture;
    }

    Texture* Texture::Create(int width, int height)
    {
        Texture* texture = new Texture();
        texture->surface = sdl2::SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        if (texture->surface == nullptr)
        {
            delete texture;
            return nullptr;
        }
        texture->texture = sdl2::SDL_CreateTexture(App::DrawWindow->renderer, sdl2::SDL_PIXELFORMAT_RGBA32, sdl2::SDL_TEXTUREACCESS_STREAMING, width, height);
        if (texture->texture == nullptr)
        {
            delete texture;
            return nullptr;
        }
        texture->isWritable = true; // Set to true if the texture is writable
        return texture;
    }

    void Texture::Free(Texture* texture)
    {
        delete texture;
    }

}