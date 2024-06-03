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
        this->activeSelf = true;
    }

    GameObject::GameObject(Scene *scene)
    {
        this->name = "GameObject";
        this->m_transform = new Transform(this);
        this->scene = scene;
        this->activeSelf = true;
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
        return this->activeSelf 
            && (this->m_transform->parent() == nullptr 
                || this->m_transform->parent()->gameObject->activeInHierarchy());
    }

    Transform *GameObject::transform()
    {
        return this->m_transform;
    }

    template <typename T_Component, typename... Args>
    T_Component *GameObject::AddComponent(Args... args)
    {
        T_Component *component = new T_Component(this, args...);
        this->components.Append(component);
        return component;
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
    
    template Component *GameObject::AddComponent<Component>();
}