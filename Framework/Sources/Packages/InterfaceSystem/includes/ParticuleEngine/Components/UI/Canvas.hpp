#ifndef PE_UI_CANVAS_HPP
#define PE_UI_CANVAS_HPP
#include <ParticuleEssential/Types/String.hpp>
#include "UiComponent.hpp"

namespace Particule::Core::UI
{
    class Canvas : public UiComponent
    {
    public:
        Canvas(GameObject *gameObject);
        ~Canvas() override;
        virtual const String __class__() { return "Canvas";}
    };
}

#endif // PE_UI_CANVAS_HPP