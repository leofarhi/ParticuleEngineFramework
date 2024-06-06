#include "../../../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
namespace Particule::Essential::Input
{
    using namespace Particule::Essential::CasioCg;
    InputManager* input = nullptr;

    Mouse::Mouse()
    {
        position = {0, 0};
    }

    Mouse::~Mouse()
    {
    }

    bool Mouse::IsPressed(int button)
    {
        
    }

    bool Mouse::IsDown(int button)
    {
        
    }

    bool Mouse::IsUp(int button)
    {
        
    }

    InputManager::InputManager()
    {
        
    }

    InputManager::~InputManager()
    {
        
    }

    List<GINT_keyinfo>* InputManager::GetInputEvents() const
    {
        return InputEvents;
    }

    List<GINT_keyinfo>* InputManager::GetInputEventsHeld() const
    {
        return InputEventsHeld;
    }

    void InputManager::Update()
    {
        
    }

    bool InputManager::IsKeyPressed(int key)
    {
        
    }

    bool InputManager::IsKeyDown(int key)
    {
        
    }

    bool InputManager::IsKeyUp(int key)
    {
        
    }

    Vector2 InputManager::GetAnalogStick(int stick)
    {
        return {0, 0};
    }
}