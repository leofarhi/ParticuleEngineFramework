#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <ParticuleEssential/Texture/Texture.hpp>
#include <ParticuleEssential/Types/Rect.hpp>

namespace Particule::Essential::Texture
{
    class Sprite
    {
    public:
        Texture* texture;
        Rect rect;
        Sprite();
        Sprite(Texture* texture, Rect rect);
        ~Sprite();
        void Draw(int x, int y);
        void DrawSize(int x, int y, int w, int h);
        void DrawColor(int x, int y, Color color);
        void DrawSizeColor(int x, int y, int w, int h, Color color);
        Sprite* CreateSubSprite(Rect rect);
    };
}

#endif // SPRITE_HPP