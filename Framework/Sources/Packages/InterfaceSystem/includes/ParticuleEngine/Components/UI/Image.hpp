#ifndef PE_UI_IMAGE_HPP
#define PE_UI_IMAGE_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>
#include "UiComponent.hpp"

namespace Particule::Core::UI
{
    using namespace Particule::Essential;
    class Image : public UiComponent
    {
    public:
        Sprite *sprite;
        Color color;

        Image(GameObject *gameObject);
        ~Image() override;

        void OnRenderUI(Canvas* canvas, RectTransform rectTransform) override;
    };
}

#endif // PE_UI_IMAGE_HPP