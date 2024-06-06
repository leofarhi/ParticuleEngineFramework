#include <ParticuleEngine/Core/Components/MeshRenderer.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>
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

    static Matrix<float> GenerateXRotationMatrix(float theta)
    {
        Matrix<float> m(3, 3);
        m(0, 0) = 1;m(0, 1) = 0;m(0, 2) = 0;
        m(1, 0) = 0;m(1, 1) = cos(theta);m(1, 2) = -sin(theta);
        m(2, 0) = 0;m(2, 1) = sin(theta);m(2, 2) = cos(theta);
        return m;
    }

    static Matrix<float> GenerateYRotationMatrix(float theta)
    {
        Matrix<float> m(3, 3);
        m(0, 0) = cos(theta);m(0, 1) = 0;m(0, 2) = -sin(theta);
        m(1, 0) = 0;m(1, 1) = 1;m(1, 2) = 0;
        m(2, 0) = sin(theta);m(2, 1) = 0;m(2, 2) = cos(theta);
        return m;
    }

    static Matrix<float> GenerateZRotationMatrix(float theta)
    {
        Matrix<float> m(3, 3);
        m(0, 0) = cos(theta);m(0, 1) = -sin(theta);m(0, 2) = 0;
        m(1, 0) = sin(theta);m(1, 1) = cos(theta);m(1, 2) = 0;
        m(2, 0) = 0;m(2, 1) = 0;m(2, 2) = 1;
        return m;
    }

    void MeshRenderer::CalculateProjection(Camera *camera)
    {
        if (this->mesh == nullptr)
            return;
        for (size_t i = 0; i < this->mesh->verticesCount; i++)
        {
            Vector3Int p = this->mesh->vertices[i].position * this->transform()->scale;
            Matrix<float> m(4, 1);
            m(0, 0) = p.x;m(1, 0) = p.y;m(2, 0) = p.z;m(3, 0) = 1;
            Matrix<float> transform(3, 1);
            transform(0, 0) = this->transform()->position.x;
            transform(1, 0) = this->transform()->position.y;
            transform(2, 0) = this->transform()->position.z;
            m = GenerateXRotationMatrix(this->transform()->rotation.x) * m;
            m = GenerateYRotationMatrix(this->transform()->rotation.y) * m;
            m = GenerateZRotationMatrix(this->transform()->rotation.z) * m;
            m(0, 0) += transform(0, 0);
            m(1, 0) += transform(1, 0);
            m(2, 0) += transform(2, 0);
            m(0, 0) -= camera->transform()->position.x;
            m(1, 0) -= camera->transform()->position.y;
            m(2, 0) -= camera->transform()->position.z;
            m = GenerateXRotationMatrix(camera->transform()->rotation.x) * m;
            m = GenerateYRotationMatrix(camera->transform()->rotation.y) * m;
            m = GenerateZRotationMatrix(camera->transform()->rotation.z) * m;
            float x = m(0, 0);
            float y = m(1, 0);
            float z = m(2, 0);
            z = z == 0 ? 1 : z;
            float f = 300 / z;
            x = x * f + camera->transform()->position.x;
            y = -y * f + camera->transform()->position.y;
            x = x + window->GetWidth() / 2;
            y = y + window->GetHeight() / 2;
            mesh->vertices[i].projected = Vector3Int(x, y, z);
            //printf("x: %f, y: %f, z: %f\n", x, y, z);
        }
    }

}