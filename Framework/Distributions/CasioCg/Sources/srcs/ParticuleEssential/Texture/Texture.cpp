#include "../../../includes/ParticuleEssential/Texture/Texture.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>
#include <ParticuleEssential/System/VirtualFile.hpp>


namespace Particule::Essential::Image
{
    using namespace Particule::Essential::Graphic;
    using Particule::Essential::Graphic::Color;
    using Particule::Essential::Image::Sprite;
    using namespace Particule::Essential::System;
    Texture::Texture()
    {
        texture = nullptr;
        path = nullptr;
        __GetPixel = nullptr;
        __DecodePixel = nullptr;
        __SetPixel = nullptr;
        _alphaValue = 0;
        isAllocated = false;
    }

    Texture::~Texture()
    {
        //TODO
    }

    int Texture::Width()
    {
        return texture->width;
    }

    int Texture::Height()
    {
        return texture->height;
    }

    bool Texture::IsWritable()
    {
        return false;
    }

    void Texture::Draw(int x, int y)
    {
        dimage(x, y, texture);
    }

    void Texture::DrawSub(int x, int y, Rect rect)
    {
        dsubimage(x, y, texture, rect.x, rect.y, rect.w, rect.h, DIMAGE_NONE);
    }

    void Texture::DrawSize(int x, int y, int w, int h)
    {
        DrawSubSize(x, y, w, h, {0, 0, texture->width, texture->height});
    }

    void Texture::DrawSubSize(int x, int y, int w, int h, Rect rect)
    {
        int sx = rect.x;
        int sy = rect.y;
        int sw = rect.w;
        int sh = rect.h;
        if (sw == w && sh == h)
        {
            DrawSub(x, y, rect);
            return;
        }
        int flipX = 0;
        int flipY = 0;
        
        if (w < 0) {
            flipX = 1;
            w = -w;
        }
        if (h < 0) {
            flipY = 1;
            h = -h;
        }
        int x2 = 0, y2 = 0;
        unsigned int sx2 = 0, sy2 = 0;
        int xinc = (sw << 16) / w;
        int yinc = (sh << 16) / h;
        //limites les bornes de la texture
        if(sx < 0) sx = 0;
        if(sy < 0) sy = 0;
        if (sx + sw > texture->width && sw > 0)
        {
            long long ratio = (long long)w * 0x10000 / sw;
            sw = texture->width - sx;
            w = sw * ratio / 0x10000;
        }
        if (sy + sh > texture->height && sh > 0)
        {
            long long ratio = (long long)h * 0x10000 / sh;
            sh = texture->height - sy;
            h = sh * ratio / 0x10000;
        }
        //limites les bornes en fonction de la taille de la fenetre
        if(x < 0) {
            sx -= x;
            w += x;
            x = 0;
        }
        if(y < 0) {
            sy -= y;
            h += y;
            y = 0;
        }
        if(x + w > window->GetWidth()) w = window->GetWidth() - x;
        if(y + h > window->GetHeight()) h = window->GetHeight() - y;
        const int alph = this->_alphaValue;
        int row = 0;
        int col = 0;
        while (row < h) {
            x2 = 0;
            col = 0;
            
            sy2 = sy + (flipY ? (sh - 1 - (y2 >> 16)) : (y2 >> 16));
            while (col < w) {
                sx2 = sx + (flipX ? (sw - 1 - (x2 >> 16)) : (x2 >> 16));
                const int dataPix = this->__GetPixel(this, sx2, sy2);
                
                if (dataPix != alph)
                {
                    gint_vram[DWIDTH * (y + row) + (x + col)] = this->__DecodePixel(this, dataPix);
                }
                
                x2 += xinc;
                col++;
            }
            
            y2 += yinc;
            row++;
        }
    }

    void Texture::DrawColor(int x, int y, Color color)
    {
        DrawSubSizeColor(x, y, texture->width, texture->height, {0, 0, texture->width, texture->height}, color);
    }

    void Texture::DrawSubColor(int x, int y, Rect rect, Color color)
    {
        DrawSubSizeColor(x, y, rect.w, rect.h, rect, color);
    }

    void Texture::DrawSizeColor(int x, int y, int w, int h, Color color)
    {
        DrawSubSizeColor(x, y, w, h, {0, 0, texture->width, texture->height}, color);
    }

    void Texture::DrawSubSizeColor(int x, int y, int w, int h, Rect rect, Color color)
    {
        int flipX = 0;
        int flipY = 0;
        int sx = rect.x;
        int sy = rect.y;
        int sw = rect.w;
        int sh = rect.h;
        
        if (w < 0) {
            flipX = 1;
            w = -w;
        }
        if (h < 0) {
            flipY = 1;
            h = -h;
        }
        int x2 = 0, y2 = 0;
        unsigned int sx2 = 0, sy2 = 0;
        int xinc = (sw << 16) / w;
        int yinc = (sh << 16) / h;
        //limites les bornes de la texture
        if(sx < 0) sx = 0;
        if(sy < 0) sy = 0;
        if (sx + sw > texture->width && sw > 0)
        {
            long long ratio = (long long)w * 0x10000 / sw;
            sw = texture->width - sx;
            w = sw * ratio / 0x10000;
        }
        if (sy + sh > texture->height && sh > 0)
        {
            long long ratio = (long long)h * 0x10000 / sh;
            sh = texture->height - sy;
            h = sh * ratio / 0x10000;
        }
        //limites les bornes en fonction de la taille de la fenetre
        if(x < 0) {
            sx -= x;
            w += x;
            x = 0;
        }
        if(y < 0) {
            sy -= y;
            h += y;
            y = 0;
        }
        if(x + w > window->GetWidth()) w = window->GetWidth() - x;
        if(y + h > window->GetHeight()) h = window->GetHeight() - y;
        const int alph = this->_alphaValue;
        int row = 0;
        int col = 0;
        while (row < h) {
            x2 = 0;
            col = 0;
            
            sy2 = sy + (flipY ? (sh - 1 - (y2 >> 16)) : (y2 >> 16));
            while (col < w) {
                sx2 = sx + (flipX ? (sw - 1 - (x2 >> 16)) : (x2 >> 16));
                const int dataPix = this->__GetPixel(this, sx2, sy2);
                
                if (dataPix != alph)
                {
                    int colPix = this->__DecodePixel(this, dataPix);
                    //multiply color
                    Color rgb(colPix);
                    Color colorRes(rgb.r * color.r / 255, rgb.g * color.g / 255, rgb.b * color.b / 255, 255);
                    gint_vram[DWIDTH * (y + row) + (x + col)] = colorRes.color;
                }
                
                x2 += xinc;
                col++;
            }
            
            y2 += yinc;
            row++;
        }
    }

    void Texture::WritePixel(int x, int y, Color color)
    {
        //TODO
    }

    void Texture::WritePixelInt(int x, int y, long long color)
    {
        //TODO
    }

    Color Texture::ReadPixel(int x, int y)
    {
        //TODO
        return COLOR_WHITE;
    }

    long long Texture::ReadPixelInt(int x, int y)
    {
        //TODO
        return 0;
    }

    void Texture::SetPixel(int x, int y, Color color)
    {
        //TODO
    }

    Color Texture::GetPixel(int x, int y)
    {
        //TODO
        return COLOR_WHITE;
    }

    Texture* Texture::Load(const char* path)
    {
        VirtualFile* img = VirtualResources::Instance->GetFile(path);
        if (img == nullptr)
            return nullptr;
        Texture* texture = new Texture();
        texture->texture = (bopti_image_t*)(img->Data());
        texture->path = path;
        texture->__GetPixel = nullptr;
        texture->__DecodePixel = nullptr;
        texture->__SetPixel = nullptr;
        texture->_alphaValue = 0;
        texture->isAllocated = false;
        return texture;
    }

    Texture* Texture::Create(int width, int height)
    {
        //TODO
        return nullptr;
    }

    Sprite* Texture::CreateSprite(Texture* texture, Rect rect)
    {
        //TODO
        return nullptr;
    }

}