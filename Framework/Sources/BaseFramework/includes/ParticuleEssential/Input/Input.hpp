#ifndef INPUT_HPP
#define INPUT_HPP
#include "../Types/Vector2.hpp"
#include "../Types/Vector2Int.hpp"

namespace Particule::Essential
{
    class Mouse
    {
    public:
        Mouse();
        ~Mouse();
        Vector2Int position;
        static bool IsButtonPressed(int button);
        static bool IsButtonDown(int button);
        static bool IsButtonUp(int button);
    };

    class InputManager
    {
    public:
        static Mouse* mouse;
        InputManager();
        ~InputManager();
        void Update();
        static bool IsKeyPressed(int key);
        static bool IsKeyDown(int key);
        static bool IsKeyUp(int key);
        static Vector2 GetAnalogStick(int stick);
    };

    extern InputManager* input;
}

#endif // INPUT_HPP