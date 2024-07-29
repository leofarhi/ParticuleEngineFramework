#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
        this->width = 396;
        this->height = 224;
        runnig = true;
        input = new InputManager(this);
    }

    Window::Window(int width, int height, const char* title)
    {
        if (Window::MainWindow == nullptr)
        {
            Window::DrawingWindow = this;
            Window::MainWindow = this;
        }
        (void)width;
        (void)height;
        (void)title;
        this->width = 396;
        this->height = 224;
        runnig = true;
        input = new InputManager(this);
    }

    Window::~Window(){
        if (runnig)
            this->Destroy();
    }

    void Window::Update()
    {
        dupdate();
    }

    void Window::Clear()
    {
        dclear(C_BLACK);
    }

    void Window::ClearColor(Color color)
    {
        dclear(color.color);
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