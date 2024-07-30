#include <ParticuleEngine/Components/UI/Canvas.hpp>

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
    }

    Canvas::~Canvas()
    {
    }

    void Canvas::OnRenderObject()
    {
        DrawRectFill(Window::MainWindow->input->mouse->position.x, Window::MainWindow->input->mouse->position.y, 80, 80, Color(255,0,0,255));
    }
}
