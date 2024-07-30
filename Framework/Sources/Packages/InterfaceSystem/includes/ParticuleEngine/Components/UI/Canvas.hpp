#ifndef PE_UI_CANVAS_HPP
#define PE_UI_CANVAS_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEngine/Core/Component.hpp>

namespace Particule::Core::UI
{
    class Canvas : public Component
    {
    public:
        Vector2Int defaultScreenSize;

        Canvas(GameObject *gameObject);
        ~Canvas() override;
        
        void OnRenderObject() override;
    };
}

#endif // PE_UI_CANVAS_HPP