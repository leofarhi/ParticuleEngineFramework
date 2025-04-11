#ifndef FONT_HPP
#define FONT_HPP
#include <ParticuleApi/System/Resource.hpp>
#include <ParticuleApi/Graphics/Color.hpp>
#include <ParticuleApi/Types/Vector2.hpp>
#include <ParticuleApi/Graphics/Image/Texture.hpp>
#include <string>

namespace Particule::Api
{
    //Abstract class
    class Font
    {
    private:
        Texture* texture;
        int size;
        unsigned int info[95*2][2];
        int y_unicode;
        bool unicode;
        int get_char_width(Texture *txt, int start, int y);
        void read_range(int i, int i_end,int w_start, int y);
        void set_all_info();
        bool get_pos(const char *c, int *i, Vector2<int>* size, Rect* src);

        Font();
        Font(const Font& other) = default;
        Font& operator=(const Font& other) = default;
    public:
        static Font* currentFont;
        Font(Texture* texture, bool unicode);
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