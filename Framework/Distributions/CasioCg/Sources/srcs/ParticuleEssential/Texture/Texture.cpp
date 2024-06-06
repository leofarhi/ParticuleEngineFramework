#include "../../../includes/ParticuleEssential/Texture/Texture.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>


namespace Particule::Essential::Image
{
    using namespace Particule::Essential::Graphic;
    using Particule::Essential::Graphic::Color;
    using Particule::Essential::Image::Sprite;
    Texture::Texture()
    {
        texture = nullptr;
    }

    Texture::~Texture()
    {
        
    }

    int Texture::Width()
    {
        
    }

    int Texture::Height()
    {
        
    }

    bool Texture::IsWritable()
    {
        
    }

    void Texture::Draw(int x, int y)
    {
        
    }

    void Texture::DrawSub(int x, int y, Rect rect)
    {
        
    }

    void Texture::DrawSize(int x, int y, int w, int h)
    {
        
    }

    void Texture::DrawSubSize(int x, int y, int w, int h, Rect rect)
    {
        
    }

    void Texture::DrawColor(int x, int y, Color color)
    {
        
    }

    void Texture::DrawSubColor(int x, int y, Rect rect, Color color)
    {
        
    }

    void Texture::DrawSizeColor(int x, int y, int w, int h, Color color)
    {
        
    }

    void Texture::DrawSubSizeColor(int x, int y, int w, int h, Rect rect, Color color)
    {
        
    }

    void Texture::WritePixel(int x, int y, Color color)
    {
        
    }

    void Texture::WritePixelInt(int x, int y, long long color)
    {
        
    }

    Color Texture::ReadPixel(int x, int y)
    {
        
    }

    long long Texture::ReadPixelInt(int x, int y)
    {
        
    }

    void Texture::SetPixel(int x, int y, Color color)
    {
        
    }

    Color Texture::GetPixel(int x, int y)
    {
        
    }

    Texture* Texture::Load(const char* path)
    {
        
    }

    Texture* Texture::Create(int width, int height)
    {
        
    }

    Sprite* Texture::CreateSprite(Texture* texture, Rect rect)
    {
        
    }

}