#ifndef PE_UI_UICOMPONENT_HPP
#define PE_UI_UICOMPONENT_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Components/UI/Canvas.hpp>

namespace Particule::Core::UI
{
    typedef struct RectTransform
    {
        Vector2Int size;
        Vector2Int anchorMax;
        Vector2Int anchorMin;
    } RectTransform;
    

    class UiComponent : public Component
    {
    public:
        bool interactable;
        RectTransform rectTransform;

        UiComponent(GameObject *gameObject);
        ~UiComponent() override;
        virtual const String __class__() { return "UiComponent";}

        virtual void OnRenderUI(Canvas* canvas, RectTransform rectTransform) {
            (void)canvas;
            (void)rectTransform;
        };

        /*static void CallOnRenderUI_InChildren(GameObject *gameObject,
                        Canvas* canvas, RectTransform rectTransform);*/
    };
}

#endif // PE_UI_UICOMPONENT_HPP