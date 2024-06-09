#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include <ParticuleEssential/Input/Input.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>
using namespace Particule::Essential::Graphic;
using namespace Particule::Essential::Input;
using namespace Particule::Essential;
using namespace Particule::Core;
using namespace Particule::Engine;

#include <DearImGui/DearImGui.hpp>
#include <stdio.h>


int main() {
    ParticuleEssentialInit();
    ParticuleEngineInit();
    window = new Window();//800, 600, "Demo");
    printf("Hello World\n");

   IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForSDLRenderer(window->window, window->renderer);
    ImGui_ImplSDLRenderer2_Init(window->renderer);


   SDL_Surface * surface = SDL_LoadBMP("../assets/sdl.bmp");
   SDL_Texture * logo = SDL_CreateTextureFromSurface(window->renderer, surface);
   SDL_FreeSurface(surface);

   SDL_Rect rect, rect2;
   rect.x = 50;
   rect.y = 20;
   rect.w = surface->w;
   rect.h = surface->h;

   rect2.x = 800;
   rect2.y = 20;
   rect2.w = 300;
   rect2.h = 300;
   window->Clear();
  input->Update();
  window->Update();

   while(true){
     SDL_Event event;
     while(SDL_PollEvent(&event)){
        ImGui_ImplSDL2_ProcessEvent(&event);
       if( event.type == SDL_QUIT ){
         exit(0);
       }else if( event.type == SDL_MOUSEBUTTONDOWN ){
         rect2.x -= 20;
       }
       
     }
     ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Hello, Dear ImGui with SDL2");
        ImGui::Text("This is just a basic Hello World!");
        ImGui::End();
        ImGui::Render();
        

     SDL_RenderClear(window->renderer);
     SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
     //SDL_RenderDrawRect(renderer, &rect2);
     SDL_RenderFillRect(window->renderer, &rect2);
     SDL_SetRenderDrawColor(window->renderer, 9, 20, 33, 255);
     SDL_RenderCopy(window->renderer, logo, NULL, &rect);
     ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), window->renderer);
     SDL_RenderPresent(window->renderer);
   }
   ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

   SDL_DestroyTexture(logo);
   ParticuleEngineQuit();
   ParticuleEssentialQuit();
   printf("Goodbye World\n");
   return 0;
}