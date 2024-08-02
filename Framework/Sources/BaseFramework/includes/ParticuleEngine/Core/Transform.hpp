#ifndef PE_CORE_TRANSFORM_HPP
#define PE_CORE_TRANSFORM_HPP

#include <ParticuleEssential/Types/Vector3.hpp>
#include <ParticuleEssential/Types/List.hpp>
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEngine/Core/Object.hpp>

namespace Particule::Core
{
    class GameObject;
    class Transform : public Object
    {
    private:
        Transform *m_parent;
        List<Transform *> m_children;
    public:
        GameObject *gameObject;
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Transform(GameObject *gameObject);
        Transform(GameObject *gameObject, Vector3 position, Vector3 rotation, Vector3 scale);
        ~Transform() = default;
        
        void SetParent(Transform *parent);
        Transform *parent();
        List<Transform *>* children();
    };
}

#endif // PE_CORE_TRANSFORM_HPP