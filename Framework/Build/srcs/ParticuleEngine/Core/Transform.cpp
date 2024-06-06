#include <ParticuleEngine/Core/Transform.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>

namespace Particule::Core
{
    Transform::Transform(GameObject *gameObject)
    {
        this->gameObject = gameObject;
        this->position = Vector3(0, 0, 0);
        this->rotation = Vector3(0, 0, 0);
        this->scale = Vector3(1, 1, 1);
        this->m_parent = nullptr;
    }

    Transform::Transform(GameObject *gameObject, Vector3 position, Vector3 rotation, Vector3 scale)
    {
        this->gameObject = gameObject;
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        this->m_parent = nullptr;
    }

    void Transform::SetParent(Transform *parent)
    {
        if (this->m_parent != nullptr)
        {
            this->m_parent->m_children.Remove(this);
        }
        this->m_parent = parent;
        parent->m_children.Append(this);
    }

    Transform *Transform::parent()
    {
        return this->m_parent;
    }

    List<Transform *> Transform::children()
    {
        return this->m_children;
    }

}