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
    GameObject* cam_go = scene->AddGameObject(new GameObject(scene, "Camera"));
    Camera* cam = cam_go->AddComponent<Camera>();
    GameObject *canvas_go = scene->AddGameObject(new GameObject(scene, "Canvas"));
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

    SceneManager::sceneManager->AddScene(&SceneHub);
    SceneManager::sceneManager->LoadScene(0);
    while(true){
        window->Clear();
        window->input->Update();
        SceneManager::sceneManager->MainLoop();
        window->Update();
    }
    window->Destroy();
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    printf("Goodbye World\n");
    return 0;
}