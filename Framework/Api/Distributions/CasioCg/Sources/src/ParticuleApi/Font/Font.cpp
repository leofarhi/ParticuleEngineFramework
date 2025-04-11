#include <ParticuleApi/Font/Font.hpp>
#include <stdexcept>

namespace Particule::Api
{
    int	Font::get_char_width(Texture *txt, int start, int y)
    {
        int width = txt->ReadPixel(start, y).A() > 128;
        int i = start + width;
        while (i < txt->Width())
        {
            Color color = txt->ReadPixel(i, y);
            if (color.A() > 128)
                return (width + 1);
            width++;
            i++;
        }
        return (width);
    }

    void Font::read_range(int i, int i_end,int w_start, int y)
    {
        int width = w_start;
        while (i < i_end)
        {
            this->info[i][0] = get_char_width(this->texture, width, y);
            this->info[i][1] = width;
            width += this->info[i][0];
            i++;
        }
    }

    void Font::set_all_info()
    {
        read_range(0, 95, 1, 0);
        if (unicode)
        {
            y_unicode = 1;
            while (y_unicode < texture->Height() && texture->ReadPixel(0, y_unicode).A() < 128)
                y_unicode++;
            if (y_unicode == texture->Height())
                throw std::runtime_error("Failed to find unicode range in font texture");
            read_range(95, 190, 1, y_unicode);
        }
        else
            y_unicode = texture->Height();
    }


    Font::Font()
    {
        texture = nullptr;
        size = 0;
    }

    Font::Font(Texture* texture, bool unicode)
    {
        this->unicode = unicode;
        this->texture = texture;
        size = 16;
        set_all_info();
    }

    Font::~Font(){}

    void Font::SetSize(int size)
    {
        this->size = size;
    }

    int Font::GetSize()
    {
        return size;
    }

    bool Font::get_pos(const char *c, int *i, Vector2<int>* size, Rect* src)
    {
        if (c[*i] < 0 && unicode)
        {
            int unicode = (c[*i] & 0x1F) << 6;
            unicode |= (c[*i + 1] & 0x3F);
            *i += 1;
            if (unicode >= 160 && unicode < 255)
            {
                int index = unicode - 160 + 95;
                int width = info[index][0];
                int start = info[index][1];
                *src = Rect{start, y_unicode + 1, width, (texture->Height() - y_unicode) - 1};
                int h = this->size;
                int w = (width * h) / (texture->Height() - y_unicode);
                size->x = w;
                size->y = h;
                return true;
            }
        }
        else if (c[*i] >= 32 && c[*i] < 127)
        {
            int index = c[*i] - 32;
            int width = info[index][0];
            int start = info[index][1];
            *src = Rect{start, 1, width, y_unicode -1};
            int h = this->size;
            int w = (width * h) / y_unicode;
            size->x = w;
            size->y = h;

            return true;
        }
        return false;
    }

    void Font::DrawText(const std::string& text, int x, int y)
    {
        int i = 0;
        while (text[i])
        {
            Vector2<int> size;
            Rect src;
            if (get_pos(text.c_str(), &i, &size, &src))
            {
                texture->DrawSubSize(x, y, size.x, size.y, src);
                x += size.x;
            }
            i++;
        }
    }

    void Font::DrawTextColor(const std::string& text, int x, int y, const Color& color)
    {
        int i = 0;
        while (text[i])
        {
            Vector2<int> size;
            Rect src;
            if (get_pos(text.c_str(), &i, &size, &src))
            {
                texture->DrawSubSizeColor(x, y, size.x, size.y, src, color);
                x += size.x;
            }
            i++;
        }
    }

    Vector2<int> Font::GetTextSize(const std::string& text)
    {
        int i = 0;
        int width = 0;
        int height = size;
        while (text[i])
        {
            Vector2<int> size;
            Rect src;
            if (get_pos(text.c_str(), &i, &size, &src))
                width += size.x;
            i++;
        }
        return Vector2<int>{width, height};
    }

    Font* Font::Load(Resource path)
    {
        if (path.data == nullptr) return nullptr;
        return (Font*)(path.data);
    }

    void Font::Free(Font* font)
    {
        (void)font;
    }
}