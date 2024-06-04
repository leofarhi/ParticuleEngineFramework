#ifndef WINDOW_HPP
#define WINDOW_HPP
#define SDL_MAIN_HANDLED
#include <ParticuleEssential/Graphic/Color.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdarg>

#include <SDL2/SDL.h>

#define DIST_LINUX//Distribution Linux

void error_exit(int exitcode, const char* format, ...);

namespace Particule::Essential::Graphic
{
    class Window
    {
    private:
        bool runnig;
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;

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
}

#endif // WINDOW_HPP