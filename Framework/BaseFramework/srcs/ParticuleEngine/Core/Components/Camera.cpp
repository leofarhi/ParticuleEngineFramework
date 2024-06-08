#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <stdio.h>

namespace Particule::Core
{
    Camera *Camera::mainCamera = nullptr;

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
            face->DrawWireframe();
            continue;
            if (face->texture != nullptr)
                face->DrawTextured();
            else
                face->DrawWireframe();
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
        this->bufferRenderer = new BufferRenderer();
        Camera::mainCamera = this;
    }

    Camera::~Camera()
    {
        delete this->bufferRenderer;
    }

    //override OnRenderImage
    void Camera::OnRenderImage()
    {
        if (Camera::mainCamera != this)
            return;
        this->bufferRenderer->Draw();
        this->bufferRenderer->Clear();
    }
}