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
    };
}

#endif // PE_UI_MASK_HPP