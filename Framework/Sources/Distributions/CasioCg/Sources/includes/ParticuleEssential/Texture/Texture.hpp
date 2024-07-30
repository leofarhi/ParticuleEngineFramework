#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <ParticuleEssential/Types/Rect.hpp>
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <gint/gint.h>
#include <gint/display.h>

namespace Particule::Essential
{
    class Sprite;

    class Texture
    {
        bopti_image_t* texture;
        String path;
        int (*__GetPixel)(bopti_image_t* texture, int x, int y);
        int (*__DecodePixel)(bopti_image_t* texture, int pixel);
        void (*__SetPixel)(bopti_image_t* texture, int x, int y, int color);
        int _alphaValue;
        bool isAllocated;
        void SetupFormatTexture();
    public:
        Texture();
        ~Texture();
        int Width();
        int Height();
        bool IsWritable();

        void Draw(int x, int y);
        void DrawSub(int x, int y, Rect rect);
        void DrawSize(int x, int y, int w, int h);
        void DrawSubSize(int x, int y, int w, int h, Rect rect);
        void DrawColor(int x, int y, Color color);
        void DrawSubColor(int x, int y, Rect rect, Color color);
        void DrawSizeColor(int x, int y, int w, int h, Color color);
        void DrawSubSizeColor(int x, int y, int w, int h, Rect rect, Color color);

        // Secure and Unsecure WritePixel and ReadPixel
        //Unsecure : Don't check if x and y are in the texture : Faster
        void WritePixel(int x, int y, Color color);
        void WritePixelInt(int x, int y, long long color);
        Color ReadPixel(int x, int y);
        long long ReadPixelInt(int x, int y);

        //Secure : Check if x and y are in the texture : Slower
        void SetPixel(int x, int y, Color color);// SetPixel is Secure : Check if x and y are in the texture
        Color GetPixel(int x, int y);// GetPixel is Secure : Check if x and y are in the texture


        static Texture* Load(const char* path);
        static Texture* Create(int width, int height);
        static Sprite* CreateSprite(Texture* texture, Rect rect);
    };
}

#endif // TEXTURE_HPP