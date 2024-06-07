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

    static void GenerateXRotationMatrix(float theta, float m[3][3])
    {
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = cos_approx(theta); m[1][2] = -sin_approx(theta);
        m[2][0] = 0; m[2][1] = sin_approx(theta); m[2][2] = cos_approx(theta);
    }

    static void GenerateYRotationMatrix(float theta, float m[3][3])
    {
        m[0][0] = cos_approx(theta); m[0][1] = 0; m[0][2] = -sin_approx(theta);
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
        m[2][0] = sin_approx(theta); m[2][1] = 0; m[2][2] = cos_approx(theta);
    }

    static void GenerateZRotationMatrix(float theta, float m[3][3])
    {
        m[0][0] = cos_approx(theta); m[0][1] = -sin_approx(theta); m[0][2] = 0;
        m[1][0] = sin_approx(theta); m[1][1] = cos_approx(theta); m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }

    void MultiplyMatrixVector(const float m[3][3], const float v[3], float result[3])
    {
        for (int i = 0; i < 3; ++i)
        {
            result[i] = 0;
            for (int j = 0; j < 3; ++j)
            {
                result[i] += m[i][j] * v[j];
            }
        }
    }



    void MeshRenderer::CalculateProjection(Camera *camera)
    {
        if (this->mesh == nullptr)
            return;

        for (size_t i = 0; i < this->mesh->verticesCount; i++)
        {
            Vector3Int p = this->mesh->vertices[i].position * this->transform()->scale;

            float m[3] = { (float)p.x, (float)p.y, (float)p.z };
            float result[3];

            float transform[3] = {
                this->transform()->position.x,
                this->transform()->position.y,
                this->transform()->position.z
            };

            float rotationMatrix[3][3];

            GenerateXRotationMatrix(this->transform()->rotation.x, rotationMatrix);
            MultiplyMatrixVector(rotationMatrix, m, result);
            for (int j = 0; j < 3; ++j) m[j] = result[j]; // Remplacement de std::copy

            GenerateYRotationMatrix(this->transform()->rotation.y, rotationMatrix);
            MultiplyMatrixVector(rotationMatrix, m, result);
            for (int j = 0; j < 3; ++j) m[j] = result[j]; // Remplacement de std::copy

            GenerateZRotationMatrix(this->transform()->rotation.z, rotationMatrix);
            MultiplyMatrixVector(rotationMatrix, m, result);
            for (int j = 0; j < 3; ++j) m[j] = result[j]; // Remplacement de std::copy

            m[0] += transform[0];
            m[1] += transform[1];
            m[2] += transform[2];

            m[0] -= camera->transform()->position.x;
            m[1] -= camera->transform()->position.y;
            m[2] -= camera->transform()->position.z;

            GenerateXRotationMatrix(camera->transform()->rotation.x, rotationMatrix);
            MultiplyMatrixVector(rotationMatrix, m, result);
            for (int j = 0; j < 3; ++j) m[j] = result[j]; // Remplacement de std::copy

            GenerateYRotationMatrix(camera->transform()->rotation.y, rotationMatrix);
            MultiplyMatrixVector(rotationMatrix, m, result);
            for (int j = 0; j < 3; ++j) m[j] = result[j]; // Remplacement de std::copy

            GenerateZRotationMatrix(camera->transform()->rotation.z, rotationMatrix);
            MultiplyMatrixVector(rotationMatrix, m, result);
            for (int j = 0; j < 3; ++j) m[j] = result[j]; // Remplacement de std::copy

            float x = m[0];
            float y = m[1];
            float z = m[2];

            z = z == 0 ? 1 : z;
            float f = 300 / z;

            x = x * f + camera->transform()->position.x;
            y = -y * f + camera->transform()->position.y;

            x = x + window->GetWidth() / 2;
            y = y + window->GetHeight() / 2;

            mesh->vertices[i].projected = Vector3Int(x, y, z);
        }
    }


}