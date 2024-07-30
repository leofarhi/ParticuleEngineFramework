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
        virtual const String __class__() { return "Image";}
    };
}

#endif // PE_UI_IMAGE_HPP