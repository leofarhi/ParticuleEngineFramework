#ifndef WINDOW_HPP
#define WINDOW_HPP
#define SDL_MAIN_HANDLED
#include <ParticuleEssential/Graphic/Color.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdarg>

void error_exit(int exitcode, const char* format, ...);

class Window
{
private:
    void* window;
    void* renderer;
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