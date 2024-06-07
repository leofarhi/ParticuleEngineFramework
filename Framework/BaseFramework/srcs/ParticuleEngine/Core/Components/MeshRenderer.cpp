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

        const Vector2Int center = Vector2Int(window->GetWidth() / 2, window->GetHeight() / 2);
        const Transform *_transform = this->transform();
        const Transform *cameraTransform = camera->transform();

        Vector3 cos_transform = Vector3(cos_approx(_transform->rotation.x),
                                        cos_approx(_transform->rotation.y),
                                        cos_approx(_transform->rotation.z));
        Vector3 sin_transform = Vector3(sin_approx(_transform->rotation.x),
                                        sin_approx(_transform->rotation.y),
                                        sin_approx(_transform->rotation.z));

        Vector3 cos_camera = Vector3(cos_approx(cameraTransform->rotation.x),
                                        cos_approx(cameraTransform->rotation.y),
                                        cos_approx(cameraTransform->rotation.z));
        Vector3 sin_camera = Vector3(sin_approx(cameraTransform->rotation.x),
                                        sin_approx(cameraTransform->rotation.y),
                                        sin_approx(cameraTransform->rotation.z));

        for (size_t i = 0; i < this->mesh->verticesCount; i++)
        {
            Vector3 m = this->mesh->vertices[i].position * _transform->scale;
            // Apply local rotation
            ApplyRotationX(m.y, m.z, cos_transform.x, sin_transform.x);
            ApplyRotationY(m.x, m.z, cos_transform.y, sin_transform.y);
            ApplyRotationZ(m.x, m.y, cos_transform.z, sin_transform.z);

            // Apply translation
            m.x += _transform->position.x - cameraTransform->position.x;
            m.y += _transform->position.y - cameraTransform->position.y;
            m.z += _transform->position.z - cameraTransform->position.z;

            // Apply camera rotation
            ApplyRotationX(m.y, m.z, cos_camera.x, sin_camera.x);
            ApplyRotationY(m.x, m.z, cos_camera.y, sin_camera.y);
            ApplyRotationZ(m.x, m.y, cos_camera.z, sin_camera.z);

            // Projection
            m.z = m.z == 0 ? 1 : m.z;
            float f = 300 / m.z;

            m.x = (m.x * f + cameraTransform->position.x) + center.x;
            m.y = (-m.y * f + cameraTransform->position.y) + center.y;

            mesh->vertices[i].projected = m;
        }
    }





}