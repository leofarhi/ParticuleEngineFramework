#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
#include <ParticuleEssential/Graphic/Window.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>
#include <ParticuleEssential/Input/Input.hpp>
#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>
#include <ParticuleEngine/Components/UI.hpp>

using namespace Particule::Essential;
using namespace Particule::Core;
using namespace Particule::Core::UI;
using namespace Particule::Engine;
using namespace Particule::SceneManagement;

#include <stdio.h>

Scene* SceneHub()
{
    printf("SceneHub\n");
    Scene* scene = new Scene("Hub");
    GameObject* cam_go = new GameObject(scene, "Camera");
    scene->AddGameObject(cam_go);
    Camera* cam = cam_go->AddComponent<Camera>();
    GameObject *canvas_go = new GameObject(scene, "Canvas");
    scene->AddGameObject(canvas_go);
    Canvas* canvas = canvas_go->AddComponent<Canvas>();

    (void)cam;
    (void)canvas;
    return scene;
}


int main() {
    ParticuleEssentialInit();
    ParticuleEngineInit();
    Window* window = new Window();//800, 600, "Demo");
    printf("Hello World\n");

    window->Clear();
    window->input->Update();
    window->Update();

    SceneManager::sceneManager->AddScene(&SceneHub);
    SceneManager::sceneManager->LoadScene(0);
    //printf("objs: %u\n",SceneManager::sceneManager->activeScene()->gameObjects.Size());
    while(true){
        window->Clear();
        window->input->Update();
        //DrawRectFill(5, 5, 80, 80, Color(255,0,0,255));
        SceneManager::sceneManager->MainLoop();
        window->Update();
    }
    window->Destroy();
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    printf("Goodbye World\n");
    return 0;
}