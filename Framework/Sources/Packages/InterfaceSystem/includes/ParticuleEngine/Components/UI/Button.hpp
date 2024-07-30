#ifndef PE_UI_BUTTON_HPP
#define PE_UI_BUTTON_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEngine/Core/Types/ParticuleEvent.hpp>
#include "UiComponent.hpp"

namespace Particule::Core::UI
{
    class Button : public UiComponent
    {
    public:
        ParticuleEvents onClick;
        
        Button(GameObject *gameObject);
        ~Button() override;
    };
}

#endif // PE_UI_BUTTON_HPP