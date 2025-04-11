#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <ParticuleApi/System/Resource.hpp>
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/Types/Rect.hpp>
#include <string>

#include <ParticuleApi/System/sdl2.hpp>

namespace Particule::Api
{
    class Sprite;

    class Texture
    {
    protected:
        sdl2::SDL_Texture* texture;
        sdl2::SDL_Surface* surface;
        bool isWritable;
        Texture();
        Texture(const Texture& other);
        Texture& operator=(const Texture& other);
    public:
        ~Texture();
        inline int Width(){ return surface->w; }
        inline int Height(){ return surface->h; }
        inline bool IsWritable(){ return isWritable; }

        void Draw(int x, int y);
        void DrawSub(int x, int y, Rect rect);
        void DrawSubSize(int x, int y, int w, int h, Rect rect);
        inline void DrawSize(int x, int y, int w, int h) { DrawSubSize(x, y, w, h, {0, 0, surface->w, surface->h});}
        void DrawSubSizeColor(int x, int y, int w, int h, Rect rect, const Color& color);
        inline void DrawColor(int x, int y, const Color& color) { DrawSubSizeColor(x, y, surface->w, surface->h, {0, 0, surface->w, surface->h}, color); }
        inline void DrawSubColor(int x, int y, Rect rect, const Color& color) { DrawSubSizeColor(x, y, rect.w, rect.h, rect, color); }
        inline void DrawSizeColor(int x, int y, int w, int h, const Color& color) { DrawSubSizeColor(x, y, w, h, {0, 0, surface->w, surface->h}, color); }

        // Secure and Unsecure WritePixel and ReadPixel
        //Unsecure : Don't check if x and y are in the texture : Faster
        inline void WritePixelRaw(int x, int y, const ColorRaw& color)
        {
            uint32_t* pixels = (uint32_t*)surface->pixels;
            pixels[y * surface->w + x] = color;
        };
        inline void WritePixel(int x, int y, const Color& color)
        {
            uint32_t* pixels = (uint32_t*)surface->pixels;
            pixels[y * surface->w + x] = (uint32_t)color.Raw();
        };
        inline ColorRaw ReadPixelRaw(int x, int y)
        {
            uint32_t* pixels = (uint32_t*)surface->pixels;
            return (ColorRaw)pixels[y * surface->w + x];
        };
        inline Color ReadPixel(int x, int y)
        {
            uint32_t* pixels = (uint32_t*)surface->pixels;
            return Color((ColorRaw)pixels[y * surface->w + x]);
        };

        //Secure : Check if x and y are in the texture : Slower
        inline void SetPixel(int x, int y, const Color& color)// SetPixel is Secure : Check if x and y are in the texture
        {
            if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
                return;
            this->WritePixel(x, y, color);
        };
        inline Color GetPixel(int x, int y)// GetPixel is Secure : Check if x and y are in the texture
        {
            if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
                return Color(0, 0, 0, 0);
            return this->ReadPixel(x, y);
        };

        //Used to draw a pixel from the texture to the screen
        //Unsecure : Don't check if x and y are in the texture and the screen : Faster
        inline void PutPixel(int xTexture, int yTexture, int xScreen, int yScreen)
        {
            ColorRaw color = this->ReadPixelRaw(xTexture, yTexture);
            this->WritePixelRaw(xScreen, yScreen, color);
        };

        Sprite* CreateSprite(Rect rect);

        static Texture* Load(Resource path);
        static Texture* Create(int width, int height);
        static void Free(Texture* texture);
    };
}

#endif // TEXTURE_HPP