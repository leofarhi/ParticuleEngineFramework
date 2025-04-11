#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <ParticuleApi/Graphics/Image/Texture.hpp>
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/Types/Rect.hpp>

namespace Particule::Api
{
    class Sprite
    {
    private:
        Texture* texture;
        Rect rect;
    public:
        Sprite() = default;
        Sprite(Texture* texture, Rect rect) : texture(texture), rect(rect) {}
        Sprite(const Sprite& other) = default;
        Sprite& operator=(const Sprite& other) = default;
        ~Sprite() = default;

        inline void SetTexture(Texture* texture)
        {
            this->texture = texture;
        }
        inline void SetRect(Rect rect)
        {
            this->rect = rect;
        }
        inline void SetRect(int x, int y, int w, int h)
        {
            rect.x = x;
            rect.y = y;
            rect.w = w;
            rect.h = h;
        }

        inline Texture* GetTexture()
        {
            return texture;
        }
        inline Rect GetRect() const
        {
            return rect;
        }

        inline void Draw(int x, int y)
        {
            texture->DrawSub(x, y, rect);
        }
        inline void DrawSize(int x, int y, int w, int h)
        {
            texture->DrawSubSize(x, y, w, h, rect);
        }
        inline void DrawColor(int x, int y, const Color& color)
        {
            texture->DrawSubColor(x, y, rect, color);
        }
        inline void DrawSizeColor(int x, int y, int w, int h, const Color& color)
        {
            texture->DrawSubSizeColor(x, y, w, h, rect, color);
        }
        inline Sprite* CreateSubSprite(Rect rect)
        {
            Rect subRect = this->rect;
            subRect.x += rect.x;
            subRect.y += rect.y;
            subRect.w = rect.w;
            subRect.h = rect.h;
            return new Sprite(texture, subRect);
        }
    };
}

#endif // SPRITE_HPP