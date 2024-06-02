#ifndef WINDOW_HPP
#define WINDOW_HPP
#define SDL_MAIN_HANDLED
#include <ParticuleEssential/Graphic/Color.hpp>


class Window
{
private:
public:
    int width;
    int height;
    Window();
    Window(int width, int height, const char* title);
    ~Window();

    void Update();
    void Clear();
    void ClearColor(Color color);
    bool IsRunning();
    void Close();
};

extern Window* window;

#endif // WINDOW_HPP