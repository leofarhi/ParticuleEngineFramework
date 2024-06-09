#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <ParticuleEngine/Core/Types/Face.hpp>
#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEngine/Components/Core/Camera.hpp>
#include <ParticuleEssential/Graphic/Draw/Line.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Graphic/Draw/Pixel.hpp>
#include <ParticuleEssential/Texture/Texture.hpp>
#include <stdio.h>
#include <math.h>

namespace Particule::Core
{
    using namespace Particule::Essential;

    Mesh::Mesh()
    {
        vertices = nullptr;
        faces = nullptr;
    }

    Mesh::Mesh(size_t verticesCount, size_t facesCount)
    {
        vertices = (Vertex *)malloc(verticesCount * sizeof(Vertex));
        for (int i = 0; i < verticesCount; i++)
            vertices[i].position = Vector3Int(0, 0, 0);
        faces = (Face **)malloc(facesCount * sizeof(Face*));
        this->verticesCount = verticesCount;
        this->facesCount = facesCount;
    }

    Mesh::~Mesh()
    {
        if (vertices)
            free(vertices);
        if (faces)
        {
            for (int i = 0; i < facesCount; i++)
                delete faces[i];
            free(faces);
        }
    }

    void Mesh::DrawInBuffer(Camera *camera)
    {
        for (int i = 0; i < facesCount; i++)
        {
            faces[i]->CalculateDepth();
            //printf("Depth: %f\n", faces[i]->depth);
            if (faces[i]->depth > faces[i]->verticesCount)
                camera->bufferRenderer->AddFace(faces[i]);
        }
    }
}