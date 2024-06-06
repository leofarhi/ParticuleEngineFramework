#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <ParticuleEssential/Types/Rect.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <SDL2/SDL.h>

namespace Particule::Essential::Image
{
    using Particule::Essential::Graphic::Color;
    class Sprite;

    class Texture
    {
        SDL_Texture* texture;
        SDL_Surface* surface;
        int width;
        int height;
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