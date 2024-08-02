#include <ParticuleEngine/Components/UI/Canvas.hpp>
#include <ParticuleEngine/Components/UI/UiComponent.hpp>

#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include <ParticuleEssential/Input/Input.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>

namespace Particule::Core::UI
{
    using namespace Particule::Essential;

    Canvas::Canvas(GameObject *gameObject) : Component(gameObject)
    {
        this->defaultScreenSize = Vector2Int(Window::MainWindow->GetWidth(),Window::MainWindow->GetHeight());
    }

    Canvas::~Canvas()
    {
    }

    void Canvas::OnRenderObject()
    {
        RectTransform rectTransform;
        rectTransform.size = this->defaultScreenSize;
        float ratioX, ratioY;
        if (rectTransform.size.x && rectTransform.size.y)
        {   
            ratioX =  (float)Window::DrawingWindow->GetWidth() / (float)rectTransform.size.x;
            ratioY =  (float)Window::DrawingWindow->GetHeight() / (float)rectTransform.size.y;
        }
        else
        {
            ratioX = 0; ratioY = 0;
        }
        rectTransform.anchorMax = Vector2(ratioX, ratioY);
        rectTransform.anchorMin = Vector2(0, 0);
        DrawRectFill(0, 0,
        rectTransform.anchorMax.x*rectTransform.size.x,
        rectTransform.anchorMax.y*rectTransform.size.y,
        Color(255,0,0,255));
        UiComponent::ChildrenRenderUI(this->gameObject, this, rectTransform);
    }
}
