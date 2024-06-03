#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include <ParticuleEssential/Input/Input.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//SDL2
#include <SDL2/SDL.h>

using namespace Particule::Essential::Graphic;
using namespace Particule::Essential::Input;
using namespace Particule::Essential::Graphic::Draw;
using namespace Particule::Essential;

#include <ParticuleEngine/ParticuleEngine.hpp>
using namespace Particule::Core;
using namespace Particule::Engine;

//https://stackoverflow.com/questions/1997171/why-does-valgrind-say-basic-sdl-program-is-leaking-memory

int main2()
{
    ParticuleEssentialInit();
    window = new Window();//800, 600, "Demo");
    Vector2Int pos = {0, 0};
    while (window->IsRunning())
    {
        window->Clear();
        input->Update();
        printf("x: %d, y: %d\n", input->mouse->position.x, input->mouse->position.y);
        if (input->IsKeyPressed(SDLK_SPACE))
            pos = input->mouse->position;
        if (input->IsKeyPressed(SDLK_UP))
            pos.y--;
        if (input->IsKeyPressed(SDLK_DOWN))
            pos.y++;
        if (input->IsKeyPressed(SDLK_LEFT))
            pos.x--;
        if (input->IsKeyPressed(SDLK_RIGHT))
            pos.x++;

        DrawRect(pos.x, pos.y, 50, 50, COLOR_RED);
        window->Update();
    }
    ParticuleEssentialQuit();
    return 0;
}



int main()
{
    ParticuleEssentialInit();
    ParticuleEngineInit();
    window = new Window();//800, 600, "Demo");
    while (window->IsRunning())
    {
        window->Clear();
        input->Update();
        window->Update();
    }
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    return 0;
}