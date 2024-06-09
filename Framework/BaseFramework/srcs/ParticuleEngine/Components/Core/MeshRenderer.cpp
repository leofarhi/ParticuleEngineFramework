#include <ParticuleEngine/Components/Core/MeshRenderer.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <ParticuleEssential/Basic/Basic.hpp>
#include <ParticuleEngine/Components/Core/Camera.hpp>
#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEssential/Types/Matrix.hpp>
#include <ParticuleEssential/Graphic/Window.hpp>
#include <math.h>
#include <stdio.h>

namespace Particule::Core
{
    using namespace Particule::Essential;
    
    MeshRenderer::MeshRenderer(GameObject *gameObject) : Component(gameObject)
    {
        this->mesh = nullptr;
    }

    MeshRenderer::~MeshRenderer()
    {
    }


    inline static void ApplyRotationX(float &y, float &z, float cos_theta, float sin_theta)
    {
        const float new_y = y * cos_theta - z * sin_theta;
        const float new_z = y * sin_theta + z * cos_theta;
        y = new_y;
        z = new_z;
    }

    inline static void ApplyRotationY(float &x, float &z, float cos_theta, float sin_theta)
    {
        const float new_x = x * cos_theta + z * sin_theta;
        const float new_z = -x * sin_theta + z * cos_theta;
        x = new_x;
        z = new_z;
    }

    inline static void ApplyRotationZ(float &x, float &y, float cos_theta, float sin_theta)
    {
        const float new_x = x * cos_theta - y * sin_theta;
        const float new_y = x * sin_theta + y * cos_theta;
        x = new_x;
        y = new_y;
    }

    void MeshRenderer::CalculateProjection(Camera *camera)
    {
        if (this->mesh == nullptr)
            return;

        const Vector2Int center(window->GetWidth() / 2, window->GetHeight() / 2);
        const Transform *_transform = this->transform();
        const Transform *cameraTransform = camera->transform();

        // Precompute cos and sin for object rotation
        const Vector3 cos_transform(cos(_transform->rotation.x), cos(_transform->rotation.y), cos(_transform->rotation.z));
        const Vector3 sin_transform(sin(_transform->rotation.x), sin(_transform->rotation.y), sin(_transform->rotation.z));

        // Precompute cos and sin for camera rotation
        const Vector3 cos_camera(cos(cameraTransform->rotation.x), cos(cameraTransform->rotation.y), cos(cameraTransform->rotation.z));
        const Vector3 sin_camera(sin(cameraTransform->rotation.x), sin(cameraTransform->rotation.y), sin(cameraTransform->rotation.z));

        const float min_z = 1;  // Define a minimum z value to avoid division by zero or too close projections

        for (size_t i = 0; i < this->mesh->verticesCount; i++)
        {
            Vector3 m = this->mesh->vertices[i].position * _transform->scale;

            // Apply local rotation
            ApplyRotationX(m.y, m.z, cos_transform.x, sin_transform.x);
            ApplyRotationY(m.x, m.z, cos_transform.y, sin_transform.y);
            ApplyRotationZ(m.x, m.y, cos_transform.z, sin_transform.z);

            // Apply translation (including inverse camera translation)
            m.x += _transform->position.x - cameraTransform->position.x;
            m.y += _transform->position.y - cameraTransform->position.y;
            m.z += _transform->position.z - cameraTransform->position.z;

            // Apply camera rotation
            ApplyRotationX(m.y, m.z, cos_camera.x, sin_camera.x);
            ApplyRotationY(m.x, m.z, cos_camera.y, sin_camera.y);
            ApplyRotationZ(m.x, m.y, cos_camera.z, sin_camera.z);

            // Projection
            float m_z = (m.z < min_z) ? min_z : m.z;  // Ensure m.z is not less than the minimum z value
            float f = 300 / m_z;

            m.x = (m.x * f) + center.x;
            m.y = (-m.y * f) + center.y;

            mesh->vertices[i].projected = Vector3Int(static_cast<int>(m.x), static_cast<int>(m.y), static_cast<int>(m.z));
        }
    }



    void MeshRenderer::OnRenderObject()
    {
        this->CalculateProjection(Camera::mainCamera);
        this->mesh->DrawInBuffer(Camera::mainCamera);
    }

}