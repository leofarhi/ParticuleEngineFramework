#include <ParticuleEngine/Components/Core/Camera.hpp>

namespace Particule::Core
{
    Camera *Camera::mainCamera = nullptr;

    Camera::Camera(GameObject *gameObject) : Component(gameObject)
    {
        Camera::mainCamera = this;
    }

    Camera::~Camera()
    {
        
    }

    //override OnRenderImage
    void Camera::OnRenderImage()
    {
        if (Camera::mainCamera != this)
            return;
        //TODO: Implement OnRenderImage
    }
}