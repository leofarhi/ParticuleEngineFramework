#include "../../../includes/ParticuleEssential/Texture/Texture.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>
#include <ParticuleEssential/System/VirtualFile.hpp>


namespace Particule::Essential
{
    static int GetPixel_CG_RGB16(bopti_image_t* texture, int x, int y){
        void *data = ((unsigned char *)texture->data) + y * texture->stride;
        uint16_t *data_u16 = (uint16_t *)data;
        return data_u16[x];
    }

    static int GetPixel_CG_P8(bopti_image_t* texture, int x, int y){
        void *data = ((unsigned char *)texture->data) + y * texture->stride;
        uint8_t *data_u8 = (uint8_t *)data;
        return (int8_t)data_u8[x];
    }

    static int GetPixel_CG_P4(bopti_image_t* texture, int x, int y){
        void *data = ((unsigned char *)texture->data) + y * texture->stride;
        uint8_t *data_u8 = (uint8_t *)data;
        return (x & 1) ? data_u8[x >> 1] & 0x0f : data_u8[x >> 1] >> 4;
    }

    static int DecodePixel_CG_RGB16(bopti_image_t* texture, int pixel){
        (void)texture;
        return pixel;
    }

    static int DecodePixel_CG_P8(bopti_image_t* texture, int pixel){
        return texture->palette[pixel+128];
    }

    static int DecodePixel_CG_P4(bopti_image_t* texture, int pixel){
        return texture->palette[pixel];
    }

    static void SetPixel_CG_RGB16(bopti_image_t* texture, int x, int y, int color){
        void *data = ((unsigned char *)texture->data) + y * texture->stride;
        uint16_t *data_u16 = (uint16_t *)data;
        data_u16[x] = color;
    }

    static void SetPixel_CG_P8(bopti_image_t* texture, int x, int y, int color){
        void *data = ((unsigned char *)texture->data) + y * texture->stride;
        uint8_t *data_u8 = (uint8_t *)data;
        data_u8[x] = color;
    }

    static void SetPixel_CG_P4(bopti_image_t* texture, int x, int y, int color){
        void *data = ((unsigned char *)texture->data) + y * texture->stride;
        uint8_t *data_u8 = (uint8_t *)data;
        if (x & 1) {
            data_u8[x >> 1] = (data_u8[x >> 1] & 0xf0) | (color & 0x0f);
        } else {
            data_u8[x >> 1] = (data_u8[x >> 1] & 0x0f) | (color << 4);
        }
    }

    void Texture::SetupFormatTexture(){
        bopti_image_t* texture = this->texture;
        if(IMAGE_IS_RGB16(texture->format)) {
            this->__GetPixel =GetPixel_CG_RGB16;
            this->__DecodePixel =DecodePixel_CG_RGB16;
            this->__SetPixel =SetPixel_CG_RGB16;
        }
        else if(IMAGE_IS_P8(texture->format)) {
            this->__GetPixel =GetPixel_CG_P8;
            this->__DecodePixel =DecodePixel_CG_P8;
            this->__SetPixel =SetPixel_CG_P8;
        }
        else if(IMAGE_IS_P4(texture->format)) {
            this->__GetPixel =GetPixel_CG_P4;
            this->__DecodePixel =DecodePixel_CG_P4;
            this->__SetPixel =SetPixel_CG_P4;
        }

        this->_alphaValue = image_alpha(texture->format);
    }


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
        if(x + w > Window::DrawingWindow->GetWidth()) w = Window::DrawingWindow->GetWidth() - x;
        if(y + h > Window::DrawingWindow->GetHeight()) h = Window::DrawingWindow->GetHeight() - y;
        const int alph = this->_alphaValue;
        int row = 0;
        int col = 0;
        while (row < h) {
            x2 = 0;
            col = 0;
            
            sy2 = sy + (flipY ? (sh - 1 - (y2 >> 16)) : (y2 >> 16));
            while (col < w) {
                sx2 = sx + (flipX ? (sw - 1 - (x2 >> 16)) : (x2 >> 16));
                const int dataPix = this->__GetPixel(this->texture, sx2, sy2);
                
                if (dataPix != alph)
                {
                    gint_vram[DWIDTH * (y + row) + (x + col)] = this->__DecodePixel(this->texture, dataPix);
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
        if(x + w > Window::DrawingWindow->GetWidth()) w = Window::DrawingWindow->GetWidth() - x;
        if(y + h > Window::DrawingWindow->GetHeight()) h = Window::DrawingWindow->GetHeight() - y;
        const int alph = this->_alphaValue;
        int row = 0;
        int col = 0;
        while (row < h) {
            x2 = 0;
            col = 0;
            
            sy2 = sy + (flipY ? (sh - 1 - (y2 >> 16)) : (y2 >> 16));
            while (col < w) {
                sx2 = sx + (flipX ? (sw - 1 - (x2 >> 16)) : (x2 >> 16));
                const int dataPix = this->__GetPixel(this->texture, sx2, sy2);
                
                if (dataPix != alph)
                {
                    int colPix = this->__DecodePixel(this->texture, dataPix);
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
        (void)x;
        (void)y;
        (void)color;
    }

    void Texture::WritePixelInt(int x, int y, long long color)
    {
        //TODO
        (void)x;
        (void)y;
        (void)color;
    }

    Color Texture::ReadPixel(int x, int y)
    {
        //TODO
        //return COLOR_WHITE;
        //Color color(x,y,0,0);
        int i = this->__GetPixel(this->texture, x, y);
        if (i == this->_alphaValue)
        {
            Color color(0, 0, 0, 0);
            return color;
        }
        else
        {
            Color color(this->__DecodePixel(this->texture, i));
            return color;
        }
    }

    long long Texture::ReadPixelInt(int x, int y)
    {
        //TODO
        (void)x;
        (void)y;
        return 0;
    }

    void Texture::SetPixel(int x, int y, Color color)
    {
        //TODO
        (void)x;
        (void)y;
        (void)color;
    }

    Color Texture::GetPixel(int x, int y)
    {
        //TODO
        (void)x;
        (void)y;
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
        texture->SetupFormatTexture();
        return texture;
    }

    Texture* Texture::Create(int width, int height)
    {
        //TODO
        (void)width;
        (void)height;
        return nullptr;
    }

    Sprite* Texture::CreateSprite(Texture* texture, Rect rect)
    {
        //TODO
        (void)texture;
        (void)rect;
        return nullptr;
    }

}