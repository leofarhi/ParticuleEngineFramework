#ifndef PE_TYPE_FACE_HPP
#define PE_TYPE_FACE_HPP

#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Texture/Texture.hpp>
#include <stdlib.h>

namespace Particule::Core
{
    using namespace Particule::Essential;

    typedef struct Vertex
    {
        Vector3Int position;
        Vector3Int projected;
    } Vertex;

    class Face
    {
    public:
        char verticesCount;
        Vertex **vertices;
        Vector2Int *uv;
        Texture *texture;
        Vector3Int normal;
        float depth;
        bool doubleSided = false;

        Face(Vertex *p1, Vertex *p2, Vertex *p3,
                Vector2Int uv1, Vector2Int uv2, Vector2Int uv3,
                Texture *texture);
        Face(Vertex *p1, Vertex *p2, Vertex *p3, Vertex *p4,
                Vector2Int uv1, Vector2Int uv2, Vector2Int uv3, Vector2Int uv4,
                Texture *texture);
        ~Face();
        void CalculateNormal();
        void DrawTextured();
        void DrawWireframe();
        void CalculateDepth();
    };
}

#endif // PE_TYPE_FACE_HPP