#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
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
    window = new Window();//800, 600, "Demo");
    printf("Hello World\n");

    window->Clear();
    input->Update();
    window->Update();

    /*while(true){
        window->Clear();
        input->Update();
        window->Update();
    }*/
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    printf("Goodbye World\n");
    return 0;
}