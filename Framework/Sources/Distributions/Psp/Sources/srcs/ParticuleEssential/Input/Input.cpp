#include "../../../includes/ParticuleEssential/Input/Input.hpp"
#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Particule::Essential
{

    Mouse::Mouse(InputManager* input)
    {
        this->input = input;
        position = {0, 0};
    }

    Mouse::~Mouse()
    {
    }

    bool Mouse::IsPressed(int button)
    {
        //TODO
        return false;
    }

    bool Mouse::IsDown(int button)
    {
        //TODO
        return false;
    }

    bool Mouse::IsUp(int button)
    {
        //TODO
        return false;
    }

    InputManager::InputManager(Window* window)
    {
        this->window = window;
        mouse = new Mouse(this);
        //TODO
    }

    InputManager::~InputManager()
    {
        delete mouse;
        //TODO
    }

    void InputManager::Update()
    {
        //TODO
    }

    bool InputManager::IsKeyPressed(int key)
    {
        //TODO
        return false;
    }

    bool InputManager::IsKeyDown(int key)
    {
        //TODO
        return false;
    }

    bool InputManager::IsKeyUp(int key)
    {
        //TODO
        return false;
    }

    Vector2 InputManager::GetAnalogStick(int stick)
    {
        (void)stick;
        return {0, 0};
    }
}