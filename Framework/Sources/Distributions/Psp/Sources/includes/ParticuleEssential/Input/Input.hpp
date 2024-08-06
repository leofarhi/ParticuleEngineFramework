#ifndef INPUT_HPP
#define INPUT_HPP
#include "../Types/Vector2.hpp"
#include "../Types/Vector2Int.hpp"

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
        Window* window;
    public:
        InputManager(Window* window);
        ~InputManager();

        Mouse* mouse;

        void Update();
        bool IsKeyPressed(int key);
        bool IsKeyDown(int key);
        bool IsKeyUp(int key);
        Vector2 GetAnalogStick(int stick);
    };
}

#endif // INPUT_HPP