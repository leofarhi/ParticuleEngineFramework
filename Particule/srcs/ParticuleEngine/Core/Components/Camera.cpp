#include <ParticuleEngine/Core/Components/Camera.hpp>

namespace Particule::Core
{
    Camera::Camera(GameObject *gameObject) : Component(gameObject)
    {
        this->fieldOfView = 60.0f;
        this->nearClipPlane = 0.3f;
        this->farClipPlane = 1000.0f;
        this->orthographic = false;
    }

    Camera::~Camera()
    {
    }
}