#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./Color.hpp"

class Window
{
private:
    bool runnig;
public:
    int width;
    int height;
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