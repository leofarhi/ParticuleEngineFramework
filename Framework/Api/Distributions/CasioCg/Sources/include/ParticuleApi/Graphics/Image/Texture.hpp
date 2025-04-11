#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <ParticuleApi/System/Resource.hpp>
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/Types/Rect.hpp>
#include <string>

#include <ParticuleApi/System/gint.hpp>

namespace Particule::Api
{
    class Sprite;

    // RGB16
    class Texture
    {
    protected:
        gint::image_t* img;
        int _alphaValue;
        bool isAllocated;

        inline virtual int _getPixel(int x, int y){
            const void* data = ((unsigned char*)img->data) + y * img->stride;
            const uint16_t* data_u16 = (uint16_t*)data;
            return data_u16[x];
        };
        inline virtual int _decodePixel(int pixel){return pixel;};

        Texture();
        Texture(const Texture& other);
        Texture& operator=(const Texture& other);
    public:
        Texture(gint::image_t* img, bool isAllocated) : img(img), _alphaValue(gint::image_alpha(img->format)), isAllocated(isAllocated) {}
        virtual ~Texture();
        inline int Width(){ return img->width; }
        inline int Height(){ return img->height; }
        inline bool IsWritable(){ return isAllocated; }

        inline void Draw(int x, int y) { gint::dimage(x, y, img); }
        inline void DrawSub(int x, int y, Rect rect) { gint::dsubimage(x, y, img, rect.x, rect.y, rect.w, rect.h, gint::DIMAGE_NONE); }
        void DrawSubSize(int x, int y, int w, int h, Rect rect);
        inline void DrawSize(int x, int y, int w, int h) { DrawSubSize(x, y, w, h, {0, 0, img->width, img->height});}
        void DrawSubSizeColor(int x, int y, int w, int h, Rect rect, const Color& color);
        inline void DrawColor(int x, int y, const Color& color) { DrawSubSizeColor(x, y, img->width, img->height, {0, 0, img->width, img->height}, color); }
        inline void DrawSubColor(int x, int y, Rect rect, const Color& color) { 
            //change w and h if the rect is too big
            if (rect.x + rect.w > img->width) rect.w = img->width - rect.x;
            if (rect.y + rect.h > img->height) rect.h = img->height - rect.y;
            DrawSubSizeColor(x, y, rect.w, rect.h, rect, color); }
        inline void DrawSizeColor(int x, int y, int w, int h, const Color& color) { DrawSubSizeColor(x, y, w, h, {0, 0, img->width, img->height}, color); }

        // Secure and Unsecure WritePixel and ReadPixel
        //Unsecure : Don't check if x and y are in the texture : Faster
        inline virtual void WritePixelRaw(int x, int y, const ColorRaw& color)
        {
            void* data = ((unsigned char*)img->data) + y * img->stride;
            uint16_t* data_u16 = (uint16_t*)data;
            data_u16[x] = color;
        };
        inline void WritePixel(int x, int y, const Color& color)
        {
            WritePixelRaw(x, y, color.Raw());
        };
        inline ColorRaw ReadPixelRaw(int x, int y)
        {
            const int i = _getPixel(x, y);
            if (i == _alphaValue) return i;
            return _decodePixel(i);
        };
        inline Color ReadPixel(int x, int y)
        {
            return Color(static_cast<ColorRaw>(ReadPixelRaw(x, y)));
        };

        //Secure : Check if x and y are in the texture : Slower
        inline virtual void SetPixel(int x, int y, const Color& color)// SetPixel is Secure : Check if x and y are in the texture
        {
            if (x < 0 || x >= img->width || y < 0 || y >= img->height || !IsWritable()) return;
            WritePixel(x, y, color);
        };
        inline Color GetPixel(int x, int y)// GetPixel is Secure : Check if x and y are in the texture
        {
            if (x < 0 || x >= img->width || y < 0 || y >= img->height) return Color(0, 0, 0, 0);
            return ReadPixel(x, y);
        };

        //Used to draw a pixel from the texture to the screen
        //Unsecure : Don't check if x and y are in the texture and the screen : Faster
        inline void PutPixel(int xTexture, int yTexture, int xScreen, int yScreen)
        {
            const int i = _getPixel(xTexture, yTexture);
            if (i == _alphaValue) return;
            gint::gint_vram[DWIDTH * (yScreen) + (xScreen)] = _decodePixel(i);
        };

        Sprite* CreateSprite(Rect rect);

        static Texture* Load(Resource path);
        static Texture* Create(int width, int height);
        static void Free(Texture* texture);
    };

    // P8
    class TextureP8 : public Texture
    {
    protected:
        inline int _getPixel(int x, int y) override
        {
            const void* data = ((unsigned char*)img->data) + y * img->stride;
            const uint8_t* data_u8 = (uint8_t*)data;
            return (int8_t)data_u8[x];
        };
        inline int _decodePixel(int pixel) override
        {
            return img->palette[pixel + 128];
        };
        TextureP8() = default;
        TextureP8(const TextureP8& other) = default;
        TextureP8& operator=(const TextureP8& other) = default;
    public:
        TextureP8(gint::image_t* img) : Texture(img, false) {}

        inline void WritePixelRaw(int x, int y, const ColorRaw& color) override {
            (void)x; (void)y; (void)color;
            // No implementation needed for P8 texture
        };
    };

    // P4
    class TextureP4 : public Texture
    {
    protected:
        inline int _getPixel(int x, int y) override
        {
            const void* data = ((unsigned char*)img->data) + y * img->stride;
            const uint8_t* data_u8 = (uint8_t*)data;
            return (x & 1) ? data_u8[x >> 1] & 0x0F : data_u8[x >> 1] >> 4;
        };
        inline int _decodePixel(int pixel) override
        {
            return img->palette[pixel];
        };
        TextureP4() = default;
        TextureP4(const TextureP4& other) = default;
        TextureP4& operator=(const TextureP4& other) = default;
    public:
        TextureP4(gint::image_t* img) : Texture(img, false) {}

        inline void WritePixelRaw(int x, int y, const ColorRaw& color) override {
            (void)x; (void)y; (void)color;
            // No implementation needed for P4 texture
        };
    };
}

#endif // TEXTURE_HPP