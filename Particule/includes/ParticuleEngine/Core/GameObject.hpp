#ifndef PE_CORE_GAMEOBJECT_HPP
#define PE_CORE_GAMEOBJECT_HPP

#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/List.hpp>
#include <ParticuleEngine/Core/Object.hpp>
#include <ParticuleEngine/Core/Transform.hpp>
#include <ParticuleEngine/Enum/Layer.hpp>
#include <ParticuleEngine/Enum/Tag.hpp>
#include <cstdarg>

namespace Particule::Core
{
    using namespace Particule::Enum;
    class Scene;
    class Component;

    class GameObject : public Object
    {
    private:
        Transform *m_transform;
    public:
        Scene *scene;
        String name;
        List<Component*> components;
        bool activeSelf;
        Layer layer;
        Tag tag;
        bool isStatic;

        GameObject();
        GameObject(Scene *scene);
        ~GameObject() override;
        virtual const String __class__() { return "GameObject";}

        bool activeInHierarchy();
        Transform *transform();

        template <typename T_Component, typename... Args>
        T_Component *AddComponent(Args... args);
        Component *GetComponent(String className);
    };

}

#endif // PE_CORE_GAMEOBJECT_HPP