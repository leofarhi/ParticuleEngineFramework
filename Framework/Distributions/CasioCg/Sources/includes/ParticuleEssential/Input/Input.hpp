#ifndef INPUT_HPP
#define INPUT_HPP
#include <ParticuleEssential/Types/Vector2.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Types/List.hpp>

#include <gint/gint.h>
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/rtc.h>

namespace Particule::Essential
{
    class Mouse
    {
    public:
        Mouse();
        ~Mouse();
        Vector2Int position;
        static bool IsPressed(int button);
        static bool IsDown(int button);
        static bool IsUp(int button);
    };

    class InputManager
    {
    private:
        List<key_event_t> InputEvents;
    public:
        List<key_event_t> *GetInputEvents();

        Mouse* mouse;
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