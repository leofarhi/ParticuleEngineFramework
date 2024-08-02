#include <ParticuleEngine/Components/UI/Image.hpp>

#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>

namespace Particule::Core::UI
{
    using namespace Particule::Essential;

    Image::Image(GameObject *gameObject) : UiComponent(gameObject)
    {
        this->sprite = nullptr;
        this->color = COLOR_WHITE;
    }

    Image::~Image()
    {
    }

    void Image::OnRenderUI(Canvas* canvas, RectTransform rectTransform)
    {
        (void)canvas;
        Rect rect = this->rectTransform.ApplyParent(rectTransform).GetRect(this->gameObject->transform());
        if (this->sprite)
        {
            if (this->color == COLOR_WHITE)
                this->sprite->DrawSize(rect.x, rect.y, rect.w, rect.h);
            else
                this->sprite->DrawSizeColor(rect.x, rect.y, rect.w, rect.h, this->color);
        }
        else
            DrawRectFill(rect.x, rect.y, rect.w, rect.h, this->color);
    }
}
