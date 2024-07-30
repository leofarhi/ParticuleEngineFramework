#include <ParticuleEngine/Components/UI/UiComponent.hpp>

namespace Particule::Core::UI
{
    UiComponent::UiComponent(GameObject *gameObject) : Component(gameObject)
    {
        this->interactable = true;
        this->rectTransform.size = Vector2Int(0, 0);
        this->rectTransform.anchorMax = Vector2Int(0, 0);
        this->rectTransform.anchorMin = Vector2Int(0, 0);
    }

    UiComponent::~UiComponent()
    {
    }

    void UiComponent::ChildrenRenderUI(GameObject *gameObject,
                                Canvas* canvas, RectTransform rectTransform)
    {
        (void)canvas;
        (void)rectTransform;
        (void)gameObject;
        for (ListNode<Transform *> *cur = nullptr; gameObject->transform()->children().ForEach(&cur);)
        {
            GameObject *child = cur->data->gameObject;
            //UiComponent *uiComponent = child->GetComponent<UiComponent>();
        }
    }
}
