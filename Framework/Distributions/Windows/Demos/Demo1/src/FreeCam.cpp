#include <ParticuleEngine/Core/Components/Freecam.hpp>
#include <ParticuleEssential/Input/Input.hpp>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

using namespace Particule::Core;

using namespace Particule::Essential::Input;


FreeCam::FreeCam(GameObject *gameObject) : Component(gameObject)
{
}

FreeCam::~FreeCam()
{
}

void FreeCam::Update()
{
    Transform *transform = this->transform();
    float speed = 5;
    float rotationSpeed = 0.01f;
    
    if (input->IsKeyPressed(SDLK_LEFT))
    {
        transform->position.x += cos(transform->rotation.y) * speed;
        transform->position.z += sin(transform->rotation.y) * speed;
    }
    if (input->IsKeyPressed(SDLK_RIGHT))
    {
        transform->position.x -= cos(transform->rotation.y) * speed;
        transform->position.z -= sin(transform->rotation.y) * speed;
    }
    if (input->IsKeyPressed(SDLK_DOWN))
    {
        transform->position.x -= sin(transform->rotation.y) * speed;
        transform->position.z += cos(transform->rotation.y) * speed;
    }
    if (input->IsKeyPressed(SDLK_UP))
    {
        transform->position.x += sin(transform->rotation.y) * speed;
        transform->position.z -= cos(transform->rotation.y) * speed;
    }
    if (input->IsKeyPressed(SDLK_PAGEUP))
        transform->position.y += speed;
    if (input->IsKeyPressed(SDLK_PAGEDOWN))
        transform->position.y -= speed;
    if (input->IsKeyPressed(SDLK_a))
        transform->rotation.y += rotationSpeed;
    if (input->IsKeyPressed(SDLK_d))
        transform->rotation.y -= rotationSpeed;
    if (input->IsKeyPressed(SDLK_w))
        transform->rotation.x += rotationSpeed;
    if (input->IsKeyPressed(SDLK_s))
        transform->rotation.x -= rotationSpeed;
    if (input->IsKeyPressed(SDLK_q))
        transform->rotation.z += rotationSpeed;
    if (input->IsKeyPressed(SDLK_e))
        transform->rotation.z -= rotationSpeed;
    
}
