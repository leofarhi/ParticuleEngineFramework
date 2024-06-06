#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>
#include <ParticuleEngine/Core/Transform.hpp>

namespace Particule::Core
{
    Component::Component(GameObject* gameObject)
    {
        this->gameObject = gameObject;
    }

    Transform* Component::transform()
    {
        return this->gameObject->transform();
    }
}