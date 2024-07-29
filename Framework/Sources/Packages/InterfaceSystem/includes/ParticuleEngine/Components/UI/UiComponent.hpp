#ifndef PE_UI_UICOMPONENT_HPP
#define PE_UI_UICOMPONENT_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEngine/Core/Component.hpp>

namespace Particule::Core::UI
{
    class UiComponent : public Component
    {
    public:
        bool interactable;
        Vector2Int size;
        Vector2Int anchorMax;
        Vector2Int anchorMin;

        UiComponent(GameObject *gameObject);
        ~UiComponent() override;
        virtual const String __class__() { return "UiComponent";}
    };
}

#endif // PE_UI_UICOMPONENT_HPP