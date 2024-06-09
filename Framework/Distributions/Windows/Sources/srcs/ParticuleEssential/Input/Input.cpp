#include "../../../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
namespace Particule::Essential
{
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
        for (ListNode<SDL_Event*> *cur=nullptr; input->GetInputEventsHeld()->ForEach(&cur);)
        {
            SDL_Event* event = (SDL_Event*)(cur->data);
            if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == button)
            {
                return true;
            }
        }
        return false;
    }

    bool Mouse::IsDown(int button)
    {
        for (ListNode<SDL_Event*> *cur=nullptr; input->GetInputEvents()->ForEach(&cur);)
        {
            SDL_Event* event = (SDL_Event*)(cur->data);
            if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == button)
            {
                return true;
            }
        }
        return false;
    }

    bool Mouse::IsUp(int button)
    {
        for (ListNode<SDL_Event*> *cur=nullptr; input->GetInputEvents()->ForEach(&cur);)
        {
            SDL_Event* event = (SDL_Event*)(cur->data);
            if (event->type == SDL_MOUSEBUTTONUP && event->button.button == button)
            {
                return true;
            }
        }
        return false;
    }

    InputManager::InputManager()
    {
        mouse = new Mouse();
        InputEvents = new List<SDL_Event*>();
        InputEventsHeld = new List<SDL_Event*>();
    }

    InputManager::~InputManager()
    {
        delete mouse;
        while (InputEvents->Size() > 0)
            free(InputEvents->Pop());
        delete InputEvents;
        while (InputEventsHeld->Size() > 0)
            free(InputEventsHeld->Pop());
        delete InputEventsHeld;
    }

    List<SDL_Event*>* InputManager::GetInputEvents() const
    {
        return InputEvents;
    }

    List<SDL_Event*>* InputManager::GetInputEventsHeld() const
    {
        return InputEventsHeld;
    }

    void InputManager::Update()
    {
        while (InputEvents->Size() > 0)
        {
            SDL_Event* event = (SDL_Event*)InputEvents->Pop();
            if (event->type == SDL_QUIT
            #if defined(DEBUG_MODE)
            || (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
            #endif
            )
            {
                exit(0);
            }
            free(event);
        }
        InputEvents->Clear();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.key.repeat 
                && !(event.type == SDL_QUIT))
                continue; // Ignore key repeats (holding down a key
            SDL_Event* eventCopy = (SDL_Event*)malloc(sizeof(SDL_Event));
            memcpy(eventCopy, &event, sizeof(SDL_Event));
            InputEvents->Append(eventCopy);
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN){
                SDL_Event* eventCopy2 = (SDL_Event*)malloc(sizeof(SDL_Event));
                memcpy(eventCopy2, &event, sizeof(SDL_Event));
                InputEventsHeld->Append(eventCopy2);
            }
            if (event.type == SDL_KEYUP){
                for (ListNode<SDL_Event*> *cur=nullptr; InputEventsHeld->ForEach(&cur);)
                {
                    SDL_Event* eventHeld = cur->data;
                    if (eventHeld->key.keysym.sym == event.key.keysym.sym){
                        cur = cur->next;
                        InputEventsHeld->Remove(eventHeld);
                        free(eventHeld);
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP){
                for (ListNode<SDL_Event*> *cur=nullptr; InputEventsHeld->ForEach(&cur);)
                {
                    SDL_Event* eventHeld = cur->data;
                    if (eventHeld->button.button == event.button.button){
                        cur = cur->next;
                        InputEventsHeld->Remove(eventHeld);
                        free(eventHeld);
                    }
                }
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                this->mouse->position.x = event.motion.x;
                this->mouse->position.y = event.motion.y;
            }
        }
    }

    bool InputManager::IsKeyPressed(int key)
    {
        for (ListNode<SDL_Event*> *cur=nullptr; input->InputEventsHeld->ForEach(&cur);)
        {
            SDL_Event* event = (SDL_Event*)(cur->data);
            if (event->type == SDL_KEYDOWN && event->key.keysym.sym == key)
            {
                return true;
            }
        }
        return false;
    }

    bool InputManager::IsKeyDown(int key)
    {
        for (ListNode<SDL_Event*> *cur=nullptr; input->InputEvents->ForEach(&cur);)
        {
            SDL_Event* event = (SDL_Event*)(cur->data);
            if (event->type == SDL_KEYDOWN && event->key.keysym.sym == key)
            {
                return true;
            }
        }
        return false;
    }

    bool InputManager::IsKeyUp(int key)
    {
        for (ListNode<SDL_Event*> *cur=nullptr; input->InputEvents->ForEach(&cur);)
        {
            SDL_Event* event = (SDL_Event*)(cur->data);
            if (event->type == SDL_KEYUP && event->key.keysym.sym == key)
            {
                return true;
            }
        }
        return false;
    }

    Vector2 InputManager::GetAnalogStick(int stick)
    {
        return {0, 0};
    }
}