#ifndef PE_UI_UICOMPONENT_HPP
#define PE_UI_UICOMPONENT_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/Vector2.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Components/UI/Canvas.hpp>
#include <ParticuleEssential/Types/Rect.hpp>

namespace Particule::Core::UI
{
    typedef struct RectTransform
    {
        Vector2Int size;
        Vector2 anchorMax;
        Vector2 anchorMin;

        RectTransform() {
            size = Vector2Int(50, 50);
            anchorMax = Vector2(1, 1);
            anchorMin = Vector2(0, 0);
        }

        RectTransform(Vector2Int size, Vector2 anchorMax, Vector2 anchorMin) {
            this->size = size;
            this->anchorMax = anchorMax;
            this->anchorMin = anchorMin;
        }

        RectTransform ApplyParent(RectTransform parent) {
            RectTransform rectTransform;
            rectTransform.size = size;
            rectTransform.anchorMax = Vector2(parent.anchorMax.x * anchorMax.x, parent.anchorMax.y * anchorMax.y);
            rectTransform.anchorMin = Vector2(parent.anchorMin.x * anchorMin.x, parent.anchorMin.y * anchorMin.y);
            return rectTransform;
        }

        Rect GetRect(Transform *transform) {
            Rect rect;
            rect.x = transform->position.x + anchorMin.x * size.x;
            rect.y = transform->position.y + anchorMin.y * size.y;
            rect.w = size.x * (anchorMax.x - anchorMin.x);
            rect.h = size.y * (anchorMax.y - anchorMin.y);
            return rect;
        }
    } RectTransform;
    

    class UiComponent : public Component
    {
    public:
        bool interactable;
        RectTransform rectTransform;

        UiComponent(GameObject *gameObject);
        ~UiComponent() override;

        virtual void OnRenderUI(Canvas* canvas, RectTransform rectTransform) {
            (void)canvas;
            (void)rectTransform;
        };

        static void ChildrenRenderUI(GameObject *gameObject,
                        Canvas* canvas, RectTransform rectTransform);
    };
}

#endif // PE_UI_UICOMPONENT_HPP