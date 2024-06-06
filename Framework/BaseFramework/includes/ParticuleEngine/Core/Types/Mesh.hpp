#ifndef PE_TYPE_MESH_HPP
#define PE_TYPE_MESH_HPP

#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Texture/Texture.hpp>
#include <ParticuleEngine/Core/Types/Face.hpp>
#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <stdlib.h>

namespace Particule::Core
{
    using namespace Particule::Essential::Image;

    class Mesh
    {
    public:
        Vertex *vertices;//array of vertices
        Face **faces;//array of faces
        size_t verticesCount;
        size_t facesCount;
        Mesh();
        Mesh(size_t verticesCount, size_t facesCount);
        ~Mesh();

        void DrawInBuffer(Camera *camera);
    };
}

#endif // PE_TYPE_MESH_HPP