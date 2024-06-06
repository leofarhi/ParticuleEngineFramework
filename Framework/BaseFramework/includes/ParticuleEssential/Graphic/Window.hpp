#ifndef WINDOW_HPP
#define WINDOW_HPP

//Replace this directive
#define DIST_NOT_IMPLEMENTED //Distribution not implemented
//All distribution start with DIST_

#include "./Color.hpp"
namespace Particule::Essential::Graphic
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

        void Update();
        void Clear();
        void ClearColor(Color color);
        bool IsRunning();
        void Close();
        int GetWidth();
        int GetHeight();
    };

    extern Window* window;
}

#endif // WINDOW_HPP