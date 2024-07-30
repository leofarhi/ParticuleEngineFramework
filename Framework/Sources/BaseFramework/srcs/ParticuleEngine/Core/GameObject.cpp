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
        this->scene = (Scene *)SceneManager::sceneManager->activeScene();
        this->m_activeSelf = true;
    }

    GameObject::GameObject(Scene *scene)
    {
        this->name = "GameObject";
        this->m_transform = new Transform(this);
        this->scene = scene;
        this->m_activeSelf = true;
    }

    GameObject::GameObject(Scene *scene, String name)
    {
        this->name = name;
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

    static void UpdateActive(GameObject *gameObject, bool value)
    {
       bool currentValue = gameObject->activeSelf();
       if (currentValue != value)
       {
           if (value)
               gameObject->CallComponent(&Component::OnEnable);
           else
               gameObject->CallComponent(&Component::OnDisable);
            List<Transform *> children = gameObject->transform()->children();
            for (ListNode<Transform *> *cur=nullptr; children.ForEach(&cur);)
                UpdateActive(cur->data->gameObject, value);
       }
    }

    void GameObject::SetActive(bool value)
    {
        bool oldValue = this->activeInHierarchy();
        if (!oldValue && this->m_activeSelf != value)
            UpdateActive(this, value);
        this->m_activeSelf = value;
    }

    void GameObject::CallComponent(void (Component::*method)())
    {
        for (ListNode<Component *> *cur=nullptr; this->components.ForEach(&cur);)
        {
            (cur->data->*method)();
        }
    }
}