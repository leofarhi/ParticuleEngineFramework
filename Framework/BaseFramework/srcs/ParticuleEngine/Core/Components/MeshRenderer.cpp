#include <ParticuleEngine/Core/Components/MeshRenderer.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <ParticuleEssential/Basic/Basic.hpp>
#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEssential/Types/Matrix.hpp>
#include <ParticuleEssential/Graphic/Window.hpp>
#include <math.h>
#include <stdio.h>

namespace Particule::Core
{
    using namespace Particule::Essential::Graphic;
    
    MeshRenderer::MeshRenderer(GameObject *gameObject) : Component(gameObject)
    {
        this->mesh = nullptr;
    }

    MeshRenderer::~MeshRenderer()
    {
    }

    inline static void GenerateXRotationMatrixAndTransform(float theta, float m[3])
    {
        const float cos_res = cos_approx(theta);
        const float sin_res = sin_approx(theta);
        const float y = m[1];
        const float z = m[2];
        m[1] = y * cos_res - z * sin_res;
        m[2] = y * sin_res + z * cos_res;
    }

    inline static void GenerateYRotationMatrixAndTransform(float theta, float m[3])
    {
        const float cos_res = cos_approx(theta);
        const float sin_res = sin_approx(theta);
        const float x = m[0];
        const float z = m[2];
        m[0] = x * cos_res + z * sin_res;
        m[2] = -x * sin_res + z * cos_res;
    }

    inline static void GenerateZRotationMatrixAndTransform(float theta, float m[3])
    {
        const float cos_res = cos_approx(theta);
        const float sin_res = sin_approx(theta);
        const float x = m[0];
        const float y = m[1];
        m[0] = x * cos_res - y * sin_res;
        m[1] = x * sin_res + y * cos_res;
    }

    void MeshRenderer::CalculateProjection(Camera *camera)
    {
        if (this->mesh == nullptr)
            return;
        const Vector2Int center = Vector2Int(window->GetWidth() / 2, window->GetHeight() / 2);
        const Transform *_transform = this->transform();
        const Transform *cameraTransform = camera->transform();
        for (size_t i = 0; i < this->mesh->verticesCount; i++)
        {
            Vector3Int p = this->mesh->vertices[i].position * _transform->scale;

            float m[3] = { (float)p.x, (float)p.y, (float)p.z };
            // Apply local rotation
            GenerateXRotationMatrixAndTransform(_transform->rotation.x, m);
            GenerateYRotationMatrixAndTransform(_transform->rotation.y, m);
            GenerateZRotationMatrixAndTransform(_transform->rotation.z, m);

            // Apply translation
            m[0] += _transform->position.x;
            m[1] += _transform->position.y;
            m[2] += _transform->position.z;

            // Apply camera translation
            m[0] -= cameraTransform->position.x;
            m[1] -= cameraTransform->position.y;
            m[2] -= cameraTransform->position.z;

            // Apply camera rotation
            GenerateXRotationMatrixAndTransform(cameraTransform->rotation.x, m);
            GenerateYRotationMatrixAndTransform(cameraTransform->rotation.y, m);
            GenerateZRotationMatrixAndTransform(cameraTransform->rotation.z, m);

            // Projection
            float x = m[0];
            float y = m[1];
            float z = m[2];

            z = z == 0 ? 1 : z;
            float f = 300 / z;

            x = x * f + camera->transform()->position.x;
            y = -y * f + camera->transform()->position.y;

            x = x + center.x;
            y = y + center.y;

            mesh->vertices[i].projected = Vector3Int(x, y, z);
        }
    }



}