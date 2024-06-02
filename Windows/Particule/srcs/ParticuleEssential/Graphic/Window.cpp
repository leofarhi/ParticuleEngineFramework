#include "../../../includes/ParticuleEssential/Graphic/Window.hpp"
#include <ParticuleEssential/Graphic/Color.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

void error_exit(int exitcode, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(exitcode);
}

Window* window = nullptr;
//Calls the constructor with the default values.
Window::Window()
{
    this->width = 800;
    this->height = 600;
    this->window = (void *)SDL_CreateWindow("Engine", 50, 50, this->width, this->height, SDL_WINDOW_SHOWN);// | SDL_WINDOW_RESIZABLE);
    if (this->window == NULL)
        error_exit(EXIT_FAILURE, "error window %s", SDL_GetError());

    this->renderer = (void *)SDL_CreateRenderer((SDL_Window *)this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL)
        error_exit(EXIT_FAILURE, "error render %s", SDL_GetError());

    SDL_SetRenderDrawBlendMode((SDL_Renderer *)this->renderer, SDL_BLENDMODE_BLEND);
    runnig = true;
}

Window::Window(int width, int height, const char* title)
{
    // Creates a window.
    this->window = (void *)SDL_CreateWindow(title, 50, 50, width, height, SDL_WINDOW_SHOWN);// | SDL_WINDOW_RESIZABLE);
    if (this->window == NULL)
        error_exit(EXIT_FAILURE, "error window %s", SDL_GetError());

    // Creates a renderer.
    this->renderer = (void *)SDL_CreateRenderer((SDL_Window *)this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL)
        error_exit(EXIT_FAILURE, "error render %s", SDL_GetError());

    //enable Alpha Blending
    SDL_SetRenderDrawBlendMode((SDL_Renderer *)this->renderer, SDL_BLENDMODE_BLEND);
    // Dispatches the events.

    this->width = width;
    this->height = height;
    runnig = true;
}

Window::~Window()
{
    SDL_DestroyRenderer((SDL_Renderer*)renderer);
    SDL_DestroyWindow((SDL_Window*)window);
    SDL_Quit();
}

void Window::Update()
{
    SDL_RenderPresent((SDL_Renderer*)renderer);
}

void Window::Clear()
{
    SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0, 0, 0, 255);
    SDL_RenderClear((SDL_Renderer*)renderer);
}

void Window::ClearColor(Color color)
{
    SDL_SetRenderDrawColor((SDL_Renderer*)renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear((SDL_Renderer*)renderer);
}

bool Window::IsRunning()
{
    return open;
}

void Window::Close()
{
    runnig = false;
}