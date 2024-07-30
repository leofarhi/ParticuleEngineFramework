#ifndef PE_CORE_CAMERA_HPP
#define PE_CORE_CAMERA_HPP

#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Core/Transform.hpp>

namespace Particule::Core
{
    class Camera : public Component
    {
    public:
        static Camera *mainCamera;
        static Camera *renderCamera;

        Camera(GameObject *gameObject);
        ~Camera() override;
        virtual const String __class__() { return "Camera";}

        void OnRenderImage() override;
    };
}

#endif // PE_CORE_CAMERA_HPP