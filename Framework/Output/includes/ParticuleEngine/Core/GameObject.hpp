#ifndef PE_CORE_GAMEOBJECT_HPP
#define PE_CORE_GAMEOBJECT_HPP

#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/List.hpp>
#include <ParticuleEngine/Core/Object.hpp>
#include <ParticuleEngine/Core/Transform.hpp>
#include <ParticuleEngine/Enum/Layer.hpp>
#include <ParticuleEngine/Enum/Tag.hpp>
#include <cstdarg>

namespace Particule::SceneManagement
{
    class Scene;
}

namespace Particule::Core
{
    using namespace Particule::Enum;
    using namespace Particule::SceneManagement;
    class Component;

    class GameObject : public Object
    {
    private:
        Transform *m_transform;
        bool m_activeSelf;
        Scene *scene;
    public:
        String name;
        List<Component*> components;
        Layer layer;
        Tag tag;
        bool isStatic;

        GameObject();
        GameObject(Scene *scene);
        ~GameObject() override;
        virtual const String __class__() { return "GameObject";}

        bool activeInHierarchy();
        Transform *transform();
        bool activeSelf();
        void SetActive(bool value);

        template <typename T_Component, typename... Args>
        T_Component *AddComponent(Args... args);
        Component *GetComponent(String className);
    };

}

#endif // PE_CORE_GAMEOBJECT_HPP