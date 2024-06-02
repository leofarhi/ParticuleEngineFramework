#ifndef INPUT_HPP
#define INPUT_HPP
#include <ParticuleEssential/Types/Vector2.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Types/List.hpp>

class Mouse
{
public:
    Vector2Int position;
    bool IsButtonPressed(int button);
    bool IsButtonDown(int button);
    bool IsButtonUp(int button);
};

class Input
{
private:
    List<void*> *InputEvents;
    List<void*> *InputEventsHeld;
public:
    static Input* Instance;

    static Mouse* mouse;
    Input();
    ~Input();
    void Update();
    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyUp(int key);
    static Vector2 GetAnalogStick(int stick);
};

#endif // INPUT_HPP