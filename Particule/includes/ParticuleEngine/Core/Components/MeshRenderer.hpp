#ifndef PE_CORE_MESHRENDERER_HPP
#define PE_CORE_MESHRENDERER_HPP

#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <ParticuleEngine/Core/Types/Face.hpp>

namespace Particule::Core
{
    class MeshRenderer : public Component
    {
    public:
        Mesh *mesh;
        MeshRenderer(GameObject *gameObject);
        ~MeshRenderer() override;
        virtual const String __class__() { return "MeshRenderer";}

        void CalculateProjection(Camera *camera);
    };
}

#endif // PE_CORE_MESHRENDERER_HPP