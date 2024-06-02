#include <ParticuleEssential/Texture/Sprite.hpp>

namespace Particule::Essential::Texture
{
    Sprite::Sprite()
    {
        texture = nullptr;
    }

    Sprite::Sprite(Texture* texture, Rect rect)
    {
        this->texture = texture;
        this->rect = rect;
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Draw(int x, int y)
    {
        texture->DrawSub(x, y, rect);
    }

    void Sprite::DrawSize(int x, int y, int w, int h)
    {
        texture->DrawSubSize(x, y, w, h, rect);
    }

    void Sprite::DrawColor(int x, int y, Color color)
    {
        texture->DrawSubColor(x, y, rect, color);
    }

    void Sprite::DrawSizeColor(int x, int y, int w, int h, Color color)
    {
        texture->DrawSubSizeColor(x, y, w, h, rect, color);
    }

    Sprite* Sprite::CreateSubSprite(Rect rect)
    {
        Rect subRect = this->rect;
        subRect.x += rect.x;
        subRect.y += rect.y;
        subRect.w = rect.w;
        subRect.h = rect.h;
        return new Sprite(texture, subRect);
    }
}