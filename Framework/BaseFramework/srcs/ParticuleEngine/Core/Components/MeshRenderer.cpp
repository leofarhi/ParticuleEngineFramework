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
            // Apply local rotation (X axis)
            {
                const float y = m.y;
                const float z = m.z;
                m.y = y * cos_transform.x - z * sin_transform.x;
                m.z = y * sin_transform.x + z * cos_transform.x;
            }
            // Apply local rotation (Y axis)
            {
                const float x = m.x;
                const float z = m.z;
                m.x = x * cos_transform.y + z * sin_transform.y;
                m.z = -x * sin_transform.y + z * cos_transform.y;
            }
            // Apply local rotation (Z axis)
            {
                const float x = m.x;
                const float y = m.y;
                m.x = x * cos_transform.z - y * sin_transform.z;
                m.y = x * sin_transform.z + y * cos_transform.z;
            }
            // Apply translation
            m.x += _transform->position.x;
            m.y += _transform->position.y;
            m.z += _transform->position.z;
            // Apply camera translation
            m.x -= cameraTransform->position.x;
            m.y -= cameraTransform->position.y;
            m.z -= cameraTransform->position.z;
            // Apply camera rotation (X axis)
            {
                const float y = m.y;
                const float z = m.z;
                m.y = y * cos_camera.x - z * sin_camera.x;
                m.z = y * sin_camera.x + z * cos_camera.x;
            }
            // Apply camera rotation (Y axis)
            {
                const float x = m.x;
                const float z = m.z;
                m.x = x * cos_camera.y + z * sin_camera.y;
                m.z = -x * sin_camera.y + z * cos_camera.y;
            }
            // Apply camera rotation (Z axis)
            {
                const float x = m.x;
                const float y = m.y;
                m.x = x * cos_camera.z - y * sin_camera.z;
                m.y = x * sin_camera.z + y * cos_camera.z;
            }

            // Projection
            m.z = m.z == 0 ? 1 : m.z;
            float f = 300 / m.z;

            m.x = m.x * f + cameraTransform->position.x;
            m.y = -m.y * f + cameraTransform->position.y;

            m.x = m.x + center.x;
            m.y = m.y + center.y;

            mesh->vertices[i].projected = m;
        }
    }





}