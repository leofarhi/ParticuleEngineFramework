#ifndef WINDOW_HPP
#define WINDOW_HPP
#define SDL_MAIN_HANDLED
#include <ParticuleEssential/Graphic/Color.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdarg>

#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/rtc.h>
#include <gint/gint.h>
#include <gint/timer.h>
#include <gint/clock.h>

#define DIST_WINDOW//Distribution window

void error_exit(int exitcode, const char* format, ...);

#include "../Input/Input.hpp"
namespace Particule::Essential
{
    class Window
    {
    private:
        int width;
        int height;
        bool runnig;
    public:

        Window();
        Window(int width, int height, const char* title);
        ~Window();

        static Window* DrawingWindow;
        static Window* MainWindow;
        InputManager* input;

        void Update();
        void Clear();
        void ClearColor(Color color);
        bool IsRunning();
        void Destroy();
        int GetWidth();
        int GetHeight();
    };
}

#endif // WINDOW_HPP