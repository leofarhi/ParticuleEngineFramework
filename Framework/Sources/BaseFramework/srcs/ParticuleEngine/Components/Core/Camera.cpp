#include <ParticuleEngine/Components/Core/Camera.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>


namespace Particule::Core
{
    using namespace Particule::SceneManagement;
    Camera *Camera::mainCamera = nullptr;
    Camera *Camera::renderCamera = nullptr;

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
        Camera::renderCamera = this;
        SceneManager::sceneManager->CallAllComponents(&Component::OnRenderObject,false);
        Camera::renderCamera = nullptr;
    }
}