#include <ParticuleEngine/Core/GameObject.hpp>
#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Core/Transform.hpp>
#include <ParticuleEngine/Scene/Scene.hpp>
#include <ParticuleEngine/Scene/SceneManager.hpp>
#include <ParticuleEssential/Types/String.hpp>

namespace Particule::Core
{
    using namespace Particule::SceneManagement;
    
    GameObject::GameObject()
    {
        this->name = "GameObject";
        this->m_transform = new Transform(this);
        this->scene = (Scene *)sceneManager->activeScene();
        this->m_activeSelf = true;
    }

    GameObject::GameObject(Scene *scene)
    {
        this->name = "GameObject";
        this->m_transform = new Transform(this);
        this->scene = scene;
        this->m_activeSelf = true;
    }

    GameObject::~GameObject()
    {
        for (ListNode<Component *> *cur=nullptr; this->components.ForEach(&cur);)
        {
            delete cur->data;
        }
        delete this->m_transform;
    }

    bool GameObject::activeInHierarchy()
    {
        return this->activeSelf() 
            && (this->m_transform->parent() == nullptr 
                || this->m_transform->parent()->gameObject->activeInHierarchy());
    }

    Transform *GameObject::transform()
    {
        return this->m_transform;
    }

    bool GameObject::activeSelf()
    {
        return this->m_activeSelf;
    }

    void GameObject::SetActive(bool value)
    {
        this->m_activeSelf = value;
    }

    Component *GameObject::GetComponent(String className)
    {
        for (ListNode<Component *> *cur=nullptr; this->components.ForEach(&cur);)
        {
            if (cur->data->__class__() == className)
            {
                return cur->data;
            }
        }
        return nullptr;
    }
}