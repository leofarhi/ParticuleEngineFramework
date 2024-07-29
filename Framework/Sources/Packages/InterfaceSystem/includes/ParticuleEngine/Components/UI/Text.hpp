#ifndef PE_UI_TEXT_HPP
#define PE_UI_TEXT_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Font/Font.hpp>
#include "UiComponent.hpp"

namespace Particule::Core::UI
{
    using namespace Particule::Essential;
    class Text : public UiComponent
    {
    public:
        Font *font;
        String text;

        Text(GameObject *gameObject);
        ~Text() override;
        virtual const String __class__() { return "Text";}
    };
}

#endif // PE_UI_TEXT_HPP