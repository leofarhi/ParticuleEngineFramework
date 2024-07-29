#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include <ParticuleEssential/Input/Input.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>
using namespace Particule::Essential;
using namespace Particule::Core;
using namespace Particule::Engine;

#include <stdio.h>


int main() {
    ParticuleEssentialInit();
    ParticuleEngineInit();
    Window* window = new Window();//800, 600, "Demo");
    printf("Hello World\n");

    window->Clear();
    window->input->Update();
    window->Update();

    while(true){
        window->Clear();
        window->input->Update();
        DrawRectFill(5, 5, 80, 80, Color(255,0,0,255));
        window->Update();
    }
    window->Destroy();
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    printf("Goodbye World\n");
    return 0;
}