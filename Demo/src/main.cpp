#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

int main()
{
    ParticuleEssentialInit();
    window = new Window(800, 600, "Demo");
    while (window->IsRunning())
    {
        window->Update();
        window->Clear();
    }
    ParticuleEssentialQuit();
    return 0;
}