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
        virtual const String __class__() { return "Component";}
        Transform *transform();

        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update() {};
        virtual void FixedUpdate() {};
        virtual void LateUpdate() {};

        virtual void OnEnable() {};
        virtual void OnDisable() {};
        virtual void OnDestroy() {};
    };
}

#endif // PE_CORE_COMPONENT_HPP