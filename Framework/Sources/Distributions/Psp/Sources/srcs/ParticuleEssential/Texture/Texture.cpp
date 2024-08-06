#include "../../../includes/ParticuleEssential/Texture/Texture.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>

namespace Particule::Essential
{

    Texture::Texture()
    {
        //TODO
    }

    Texture::~Texture()
    {
        //TODO
    }

    int Texture::Width()
    {
        return 0;//TODO width;
    }

    int Texture::Height()
    {
        return 0;//TODO height;
    }

    bool Texture::IsWritable()
    {
        return 0;//TODO surface != nullptr;
    }

    void Texture::Draw(int x, int y)
    {
        //TODO
    }

    void Texture::DrawSub(int x, int y, Rect rect)
    {
        //TODO
    }

    void Texture::DrawSize(int x, int y, int w, int h)
    {
        //TODO
    }

    void Texture::DrawSubSize(int x, int y, int w, int h, Rect rect)
    {
        //TODO
    }

    void Texture::DrawColor(int x, int y, Color color)
    {
        //TODO
    }

    void Texture::DrawSubColor(int x, int y, Rect rect, Color color)
    {
        //TODO
    }

    void Texture::DrawSizeColor(int x, int y, int w, int h, Color color)
    {
        //TODO
    }

    void Texture::DrawSubSizeColor(int x, int y, int w, int h, Rect rect, Color color)
    {
        //TODO
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
        return Color();
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
        return Color();
    }

    Texture* Texture::Load(const char* path)
    {
        //TODO
        return nullptr;
    }

    Texture* Texture::Create(int width, int height)
    {
        //TODO
        return nullptr;
    }

    Sprite* Texture::CreateSprite(Texture* texture, Rect rect)
    {
        return new Sprite(texture, rect);
    }

}