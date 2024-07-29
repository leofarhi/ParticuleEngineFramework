#ifndef PE_UI_MASK_HPP
#define PE_UI_MASK_HPP
#include <ParticuleEssential/Types/String.hpp>
#include "UiComponent.hpp"

namespace Particule::Core::UI
{
    class Mask : public UiComponent
    {
    public:
        Mask(GameObject *gameObject);
        ~Mask() override;
        virtual const String __class__() { return "Mask";}
    };
}

#endif // PE_UI_MASK_HPP