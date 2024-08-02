#include <ParticuleEngine/Components/UI/UiComponent.hpp>

namespace Particule::Core::UI
{
    UiComponent::UiComponent(GameObject *gameObject) : Component(gameObject)
    {
        this->interactable = true;
        this->rectTransform.size = Vector2Int(50, 50);
        this->rectTransform.anchorMax = Vector2Int(1, 1);
        this->rectTransform.anchorMin = Vector2Int(0, 0);
    }

    UiComponent::~UiComponent()
    {
    }

    void UiComponent::ChildrenRenderUI(GameObject *gameObject,
                                Canvas* canvas, RectTransform rectTransform)
    {
        for (ListNode<Transform *> *cur = nullptr; gameObject->transform()->children()->ForEach(&cur);)
        {
            GameObject *child = cur->data->gameObject;
            List<UiComponent *> uiComponents = child->GetComponents<UiComponent>();
            for (ListNode<UiComponent *> *cur2 = nullptr; uiComponents.ForEach(&cur2);)
            {
                cur2->data->OnRenderUI(canvas, rectTransform);
            }
        }
    }
}
