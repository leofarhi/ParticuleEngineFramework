#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error_exit(int exitcode, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(exitcode);
}

namespace Particule::Essential
{
    Window* window = nullptr;
    //Calls the constructor with the default values.
    Window::Window()
    {
        this->width = 800;
        this->height = 600;
        this->window = SDL_CreateWindow("Engine", 50, 50, this->width, this->height, SDL_WINDOW_SHOWN);// | SDL_WINDOW_RESIZABLE);
        if (this->window == NULL)
            error_exit(EXIT_FAILURE, "error window %s", SDL_GetError());

        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
        if (this->renderer == NULL)
            error_exit(EXIT_FAILURE, "error render %s", SDL_GetError());

        SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
        runnig = true;
    }

    Window::Window(int width, int height, const char* title)
    {
        // Creates a window.
        this->window = SDL_CreateWindow(title, 50, 50, width, height, SDL_WINDOW_SHOWN);// | SDL_WINDOW_RESIZABLE);
        if (this->window == NULL)
            error_exit(EXIT_FAILURE, "error window %s", SDL_GetError());

        // Creates a renderer.
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
        if (this->renderer == NULL)
            error_exit(EXIT_FAILURE, "error render %s", SDL_GetError());

        //enable Alpha Blending
        SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

        this->width = width;
        this->height = height;
        runnig = true;
    }

    Window::~Window()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Window::Update()
    {
        SDL_RenderPresent(renderer);
    }

    void Window::Clear()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void Window::ClearColor(Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);
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