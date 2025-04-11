#include <ParticuleApi/Graphics/Image/Texture.hpp>
#include <ParticuleApi/Graphics/Image/Sprite.hpp>
#include <ParticuleApi/Types/Fixed.hpp>
#include <ParticuleApi/Types/Vector2.hpp>
#include <ParticuleApi/System/gint.hpp>
#include <algorithm>

namespace Particule::Api
{
    struct Sampler2D {
        Vector2<int> iteration;         // Boucle for (x, y)
        Vector2<int> screenOffset;      // Coordonnées de départ écran (x, y)
        Vector2<int> textureOffset;     // Coordonnées de départ texture (sx, sy)
        Vector2<fixed_t> TexIncr;       // Incrément en fixed pour la texture (xinc, yinc)
    
        Sampler2D(int x, int y, int w, int h, Rect rect, int screenW, int screenH, int texW, int texH)
        {
            if (w == 0 || h == 0 || rect.w == 0 || rect.h == 0)
                return;
            Vector2<fixed_t> uv_start = { fixed_t(std::clamp(rect.x, 0, texW - 1)), fixed_t(std::clamp(rect.y, 0, texH - 1)) };
            Vector2<fixed_t> uv_end = { fixed_t(std::clamp(rect.x + rect.w - 1, 0, texW - 1)), fixed_t(std::clamp(rect.y + rect.h - 1, 0, texH - 1)) };
            if (w < 0) {
                std::swap(uv_start.x, uv_end.x);
                w = -w;
            }
            if (h < 0) {
                std::swap(uv_start.y, uv_end.y);
                h = -h;
            }
            screenOffset.x = std::max(0, x);
            screenOffset.y = std::max(0, y);
            int endX = std::min(screenW - 1, x + w - 1);
            int endY = std::min(screenH - 1, y + h - 1);
            iteration.x = endX - screenOffset.x + 1;
            iteration.y = endY - screenOffset.y + 1;
            if (iteration.x <= 0 || iteration.y <= 0)
                return;
            int drawW = w - 1;
            int drawH = h - 1;
            TexIncr.x = (drawW > 0) ? ((uv_end.x - uv_start.x) / drawW) : fixed_t(0);
            TexIncr.y = (drawH > 0) ? ((uv_end.y - uv_start.y) / drawH) : fixed_t(0);
            textureOffset.x = uv_start.x + TexIncr.x * (screenOffset.x - x);
            textureOffset.y = uv_start.y + TexIncr.y * (screenOffset.y - y);
        }

    
        inline int GetScreenX(int col) const {
            return screenOffset.x + col;
        }
    
        inline int GetScreenY(int row) const {
            return screenOffset.y + row;
        }
    
        inline int GetTexX(fixed_t x2) const {
            return textureOffset.x + x2;
        }
    
        inline int GetTexY(fixed_t y2) const {
            return textureOffset.y + y2;
        }
    };

    Texture::Texture() : img(nullptr), _alphaValue(0), isAllocated(false) {}

    Texture::Texture(const Texture& other) : img(other.img), _alphaValue(other._alphaValue), isAllocated(other.isAllocated) {}

    Texture& Texture::operator=(const Texture& other)
    {
        if (this != &other)
        {
            img = other.img;
            _alphaValue = other._alphaValue;
            isAllocated = other.isAllocated;
        }
        return *this;
    }

    Texture::~Texture() {
        if (isAllocated && img != nullptr)
        {
            image_free(img);
            img = nullptr;
        }
    }

    void Texture::DrawSubSize(int x, int y, int w, int h, Rect rect)
    {
        if (rect.w == w && rect.h == h) {
            DrawSub(x, y, rect);
            return;
        }
        if (w == 0 || h == 0 || rect.w == 0 || rect.h == 0) return;
        Sampler2D sampler(x, y, w, h, rect, DWIDTH, DHEIGHT, img->width, img->height);
        fixed_t y2 = 0;
        for (int row = 0; row < sampler.iteration.y; ++row)
        {
            const int screenY = sampler.GetScreenY(row);
            const int texY = sampler.GetTexY(y2);

            fixed_t x2 = 0;
            for (int col = 0; col < sampler.iteration.x; ++col)
            {
                PutPixel(sampler.GetTexX(x2), texY, sampler.GetScreenX(col), screenY);
                x2 += sampler.TexIncr.x;
            }
            y2 += sampler.TexIncr.y;
        }
    }

    void Texture::DrawSubSizeColor(int x, int y, int w, int h, Rect rect, const Color& color)
    {
        if (color.A() < 128) return;
        if (w == 0 || h == 0 || rect.w == 0 || rect.h == 0) return;
        Sampler2D sampler(x, y, w, h, rect, DWIDTH, DHEIGHT, img->width, img->height);
        fixed_t y2 = 0;
        for (int row = 0; row < sampler.iteration.y; ++row)
        {
            const int screenY = sampler.GetScreenY(row);
            const int texY = sampler.GetTexY(y2);

            fixed_t x2 = 0;
            for (int col = 0; col < sampler.iteration.x; ++col)
            {
                const int i = _getPixel(sampler.GetTexX(x2), texY);
                if (i == _alphaValue) return;
                gint::gint_vram[DWIDTH * (screenY) + (sampler.GetScreenX(col))] = Color::MultiplyColorRaw(_decodePixel(i), color.Raw());
                x2 += sampler.TexIncr.x;
            }
            y2 += sampler.TexIncr.y;
        }
    }

    Sprite* Texture::CreateSprite(Rect rect)
    {
        return new Sprite(this, rect);
    }

    Texture* Texture::Load(Resource path)
    {
        if (path.data == nullptr) return nullptr;
        return (Texture*)(path.data);
    }

    Texture* Texture::Create(int width, int height)
    {
        gint::image_t* img = image_alloc(width,height,gint::IMAGE_RGB565A);
        if (img == nullptr) return nullptr;
        Texture* texture = new Texture(img, true);
        if (texture == nullptr) {
            image_free(img);
            return nullptr;
        }
        return texture;
    }

    void Texture::Free(Texture* texture)
    {
        if (texture != nullptr && texture->isAllocated && texture->img != nullptr)
            delete texture;
    }

}