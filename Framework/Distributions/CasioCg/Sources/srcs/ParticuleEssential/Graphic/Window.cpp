#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace Particule::Essential::Graphic
{
    Window* window = nullptr;
    //Calls the constructor with the default values.
    Window::Window()
    {
        this->width = 800;
        this->height = 600;
        
        runnig = true;
    }

    Window::Window(int width, int height, const char* title)
    {
        
        runnig = true;
    }

    Window::~Window()
    {
        
    }

    void Window::Update()
    {
        
    }

    void Window::Clear()
    {
        
    }

    void Window::ClearColor(Color color)
    {
        
    }

    bool Window::IsRunning()
    {
        return this->runnig;
    }

    void Window::Close()
    {
        runnig = false;
    }

    int Window::GetWidth()
    {
        return width;
    }

    int Window::GetHeight()
    {
        return height;
    }
}