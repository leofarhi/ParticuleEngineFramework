#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>

namespace Particule::Core
{
    Camera *Camera::main = nullptr;
    
    BufferRenderer::BufferRenderer()
    {
    }

    BufferRenderer::~BufferRenderer()
    {
    }

    void BufferRenderer::Clear()
    {
        this->faces.Clear();
    }

    void BufferRenderer::Draw()
    {
        this->Sort();
        for (size_t i = 0; i < this->faces.Size(); i++)
        {
            Face *face = this->faces[i];
            face->DrawTextured();
        }
    }

    void BufferRenderer::AddFace(Face *face)
    {
        this->faces.Append(face);
    }

    void BufferRenderer::Sort()
    {
        for (size_t i = 0; i < this->faces.Size(); i++)
        {
            for (size_t j = 0; j < this->faces.Size() - 1; j++)
            {
                if (this->faces[j]->depth < this->faces[j + 1]->depth)
                {
                    Face *temp = this->faces[j];
                    this->faces[j] = this->faces[j + 1];
                    this->faces[j + 1] = temp;
                }
            }
        }
    }

    Camera::Camera(GameObject *gameObject) : Component(gameObject)
    {
        this->fieldOfView = 60.0f;
        this->nearClipPlane = 0.3f;
        this->farClipPlane = 1000.0f;
        this->orthographic = false;
        Camera::main = this;
    }

    Camera::~Camera()
    {
    }
}