#ifndef FONT_HPP
#define FONT_HPP
#include <ParticuleApi/System/Resource.hpp>
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/Types/Vector2.hpp>
#include <string>

namespace Particule::Api
{
    //Abstract class
    class Font
    {
    private:
        Font();
        Font(const Font& other);
        Font& operator=(const Font& other);
    public:
        static Font* currentFont;
        ~Font();
    
        void SetSize(int size);
        int GetSize();
        void DrawText(const std::string& text, int x, int y);
        void DrawTextColor(const std::string& text, int x, int y, const Color& color);
        Vector2<int> GetTextSize(const std::string& text);
        
        static Font* Load(Resource path);
        static void Free(Font* texture);
    };
}

#endif // FONT_HPP