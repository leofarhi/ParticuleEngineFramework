#ifndef PE_CORE_CAMERA_HPP
#define PE_CORE_CAMERA_HPP

#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Core/Transform.hpp>
#include <ParticuleEngine/Core/Types/Face.hpp>

namespace Particule::Core
{
    
    class BufferRenderer
    {
        List<Face*> faces;
        void Sort();
    public:
        BufferRenderer();
        ~BufferRenderer();
        void Clear();
        void Draw();
        void AddFace(Face *face);
    };
    class Camera : public Component
    {
    public:
        static Camera *mainCamera;
        
        BufferRenderer *bufferRenderer;
        float fieldOfView;
        float nearClipPlane;
        float farClipPlane;
        bool orthographic;

        Camera(GameObject *gameObject);
        ~Camera() override;
        virtual const String __class__() { return "Camera";}

        void OnRenderImage() override;
    };
}

#endif // PE_CORE_CAMERA_HPP