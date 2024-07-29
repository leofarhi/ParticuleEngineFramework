#ifndef INPUT_HPP
#define INPUT_HPP
#include <ParticuleEssential/Types/Vector2.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Types/List.hpp>

#include <SDL2/SDL.h>

namespace Particule::Essential
{
    class InputManager;

    class Mouse
    {
    private:
        InputManager* input;
    public:
        Mouse(InputManager* input);
        ~Mouse();
        Vector2Int position;
        bool IsPressed(int button);
        bool IsDown(int button);
        bool IsUp(int button);
    };

    class Window;

    class InputManager
    {
    private:
        List<SDL_Event*> *InputEvents;
        List<SDL_Event*> *InputEventsHeld;
        Window* window;
    public:
        List<SDL_Event*> *GetInputEvents() const;
        List<SDL_Event*> *GetInputEventsHeld() const;

        Mouse* mouse;

        InputManager(Window* window);
        ~InputManager();
        void Update();
        bool IsKeyPressed(int key);
        bool IsKeyDown(int key);
        bool IsKeyUp(int key);
        Vector2 GetAnalogStick(int stick);
    };
}

#endif // INPUT_HPP