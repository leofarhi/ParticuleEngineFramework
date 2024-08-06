#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Particule::Essential
{
    Window* Window::DrawingWindow = nullptr;
    Window* Window::MainWindow = nullptr;
    //Calls the constructor with the default values.
    Window::Window()
    {
        if (Window::MainWindow == nullptr)
        {
            Window::DrawingWindow = this;
            Window::MainWindow = this;
        }
        this->input = new InputManager(this);
        runnig = true;
    }

    Window::Window(int width, int height, const char* title)
    {
        if (Window::MainWindow == nullptr)
        {
            Window::DrawingWindow = this;
            Window::MainWindow = this;
        }
        this->input = new InputManager(this);
        (void)width;
        (void)height;
        runnig = true;
    }

    Window::~Window()
    {
        if (runnig)
            this->Destroy();
    }

    void Window::Update()
    {
        //TODO
    }

    void Window::Clear()
    {
        //TODO
    }

    void Window::ClearColor(Color color)
    {
        //TODO
    }

    bool Window::IsRunning()
    {
        return this->runnig;
    }

    void Window::Destroy()
    {
        runnig = false;
        delete input;
        if (DrawingWindow == this)
            DrawingWindow = nullptr;
        if (MainWindow == this)
            MainWindow = nullptr;
        //TODO
    }

    int Window::GetWidth()
    {
        return 480;
    }

    int Window::GetHeight()
    {
        return 272;
    }
}