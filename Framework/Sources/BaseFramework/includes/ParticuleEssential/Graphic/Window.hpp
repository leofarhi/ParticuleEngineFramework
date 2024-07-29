#ifndef WINDOW_HPP
#define WINDOW_HPP

//Replace this directive
#define DIST_NOT_IMPLEMENTED //Distribution not implemented
//All distribution start with DIST_

#include "./Color.hpp"
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