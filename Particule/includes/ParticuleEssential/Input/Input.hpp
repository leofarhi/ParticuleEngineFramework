#ifndef INPUT_HPP
#define INPUT_HPP
#include "../Types/Vector2.hpp"
#include "../Types/Vector2Int.hpp"

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
public:
    static Mouse mouse;
    Input();
    ~Input();
    void Update();
    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyUp(int key);
    static Vector2 GetAnalogStick(int stick);
};

#endif // INPUT_HPP