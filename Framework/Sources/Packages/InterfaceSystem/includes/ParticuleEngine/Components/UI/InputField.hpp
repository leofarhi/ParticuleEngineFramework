#ifndef PE_UI_INPUTFIELD_HPP
#define PE_UI_INPUTFIELD_HPP
#include <ParticuleEssential/Types/String.hpp>
#include "UiComponent.hpp"

namespace Particule::Core::UI
{
    class InputField : public UiComponent
    {
    public:
        String text;

        InputField(GameObject *gameObject);
        ~InputField() override;
    };
}

#endif // PE_UI_INPUTFIELD_HPP