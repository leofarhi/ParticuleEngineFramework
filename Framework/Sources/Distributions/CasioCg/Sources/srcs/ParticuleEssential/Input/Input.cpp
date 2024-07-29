#include "../../../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
namespace Particule::Essential
{
    Mouse::Mouse(InputManager* input)
    {
        (void)input;
        position = {0, 0};
    }

    Mouse::~Mouse()
    {
    }

    bool Mouse::IsPressed(int button)
    {
        return InputManager::Instance->IsKeyPressed(button);
    }

    bool Mouse::IsDown(int button)
    {
        return InputManager::Instance->IsKeyDown(button);
    }

    bool Mouse::IsUp(int button)
    {
        return InputManager::Instance->IsKeyUp(button);
    }

    InputManager* InputManager::Instance = nullptr;

    InputManager::InputManager(Window* window){
        (void)window;
        InputManager::Instance = this;
    }

    InputManager::~InputManager(){}

    List<key_event_t> *InputManager::GetInputEvents()
    {
        return &InputEvents;
    }

    void InputManager::Update()
    {
        //clearevents();
        InputEvents.Clear();
        key_event_t ev;
        while((ev = pollevent()).type != KEYEV_NONE)
            InputEvents.Append(ev);
    }

    bool InputManager::IsKeyPressed(int key)
    {
        return keydown(key);
    }

    bool InputManager::IsKeyDown(int key)
    {
        for (ListNode<key_event_t> *cur=nullptr; this->GetInputEvents()->ForEach(&cur);)
        {
            key_event_t event = cur->data;
            if (event.type == KEYEV_DOWN && event.key == key)
                return true;
        }
        return false;
    }

    bool InputManager::IsKeyUp(int key)
    {
        for (ListNode<key_event_t> *cur=nullptr; this->GetInputEvents()->ForEach(&cur);)
        {
            key_event_t event = cur->data;
            if (event.type == KEYEV_UP && event.key == key)
                return true;
        }
        return false;
    }

    Vector2 InputManager::GetAnalogStick(int stick)
    {
        return {0, 0};
    }
}