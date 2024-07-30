#ifndef PE_CORE_COMPONENT_HPP
#define PE_CORE_COMPONENT_HPP

#include <ParticuleEngine/Core/Object.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>

namespace Particule::Core
{
    class Component : public Object
    {
    public:
        GameObject *gameObject;
        Component(GameObject *gameObject);

        virtual ~Component() = default;
        Transform *transform();

        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update() {};
        virtual void FixedUpdate() {};
        virtual void LateUpdate() {};

        virtual void OnEnable() {};
        virtual void OnDisable() {};
        virtual void OnDestroy() {};

        virtual void OnRenderObject() {};
        virtual void OnRenderImage() {};
    };

    template <typename T_Component, typename... Args>
    T_Component *GameObject::AddComponent(Args... args)
    {
        T_Component *component = new T_Component(this, args...);
        components.Append(component);
        return component;
    }

    template <typename T_Component>
    T_Component *GameObject::GetComponent()
    {
        for (ListNode<Component *> *cur = nullptr; components.ForEach(&cur);)
        {
            T_Component *component = dynamic_cast<T_Component *>(cur->data);
            if (component != nullptr)
                return component;
        }
        return nullptr;
    }

    template <typename T_Component>
    List<T_Component *> GameObject::GetComponents()
    {
        List<T_Component *> list;
        for (ListNode<Component *> *cur = nullptr; components.ForEach(&cur);)
        {
            T_Component *component = dynamic_cast<T_Component *>(cur->data);
            if (component != nullptr)
                list.Append(component);
        }
        return list;
    }
}

#endif // PE_CORE_COMPONENT_HPP