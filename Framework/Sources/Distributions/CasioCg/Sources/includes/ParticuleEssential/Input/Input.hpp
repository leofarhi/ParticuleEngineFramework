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
    class InputManager;

    class Mouse
    {
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
        List<key_event_t> InputEvents;
    public:
        static InputManager* Instance;
        List<key_event_t> *GetInputEvents();

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