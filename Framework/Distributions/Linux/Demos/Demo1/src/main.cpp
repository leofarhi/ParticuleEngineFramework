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
#include <ParticuleEngine/Scene/Scene.hpp>
#include <ParticuleEngine/Scene/SceneManager.hpp>
using namespace Particule::Core;
using namespace Particule::Engine;
using namespace Particule::SceneManagement;

//https://stackoverflow.com/questions/1997171/why-does-valgrind-say-basic-sdl-program-is-leaking-memory

/*int main2()
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
}*/


#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <ParticuleEngine/Core/Components/MeshRenderer.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>
#include <ParticuleEngine/Core/Types/Mesh.hpp>

#include <ParticuleEssential/Texture/Texture.hpp>
using namespace Particule::Essential::Image;

MeshRenderer *meshrender = nullptr;

Scene *LoadScene1()
{
    Texture *texture = Texture::Load("../texture.jpg");
    printf("Texture: %p\n", texture);
    Scene *scene = new Scene("Scene1");
    GameObject *go = new GameObject(scene);
    go->AddComponent<Camera>();
    Mesh *mesh = new Mesh(8,6);

    int size = 100;
    mesh->vertices[0].position = Vector3Int(-size, size, size);
    mesh->vertices[1].position = Vector3Int(size, size, size);
    mesh->vertices[2].position = Vector3Int(size, -size, size);
    mesh->vertices[3].position = Vector3Int(-size, -size, size);
    mesh->vertices[4].position = Vector3Int(-size, size, -size);
    mesh->vertices[5].position = Vector3Int(size, size, -size);
    mesh->vertices[6].position = Vector3Int(size, -size, -size);
    mesh->vertices[7].position = Vector3Int(-size, -size, -size);

    int w = texture->Width();
    int h = texture->Height();
    mesh->faces[0] = new Face(&mesh->vertices[1], &mesh->vertices[0], &mesh->vertices[3], &mesh->vertices[2],
                    Vector2Int(0, 0), Vector2Int(w-1, 0), Vector2Int(w-1, h-1), Vector2Int(0, h-1), texture);
    mesh->faces[1] = new Face(&mesh->vertices[4], &mesh->vertices[5], &mesh->vertices[6], &mesh->vertices[7],
                    Vector2Int(0, 0), Vector2Int(w-1, 0), Vector2Int(w-1, h-1), Vector2Int(0, h-1), texture);
    mesh->faces[2] = new Face(&mesh->vertices[0], &mesh->vertices[1], &mesh->vertices[5], &mesh->vertices[4],
                    Vector2Int(0, 0), Vector2Int(w-1, 0), Vector2Int(w-1, h-1), Vector2Int(0, h-1), texture);
    mesh->faces[3] = new Face(&mesh->vertices[2], &mesh->vertices[3], &mesh->vertices[7], &mesh->vertices[6],
                    Vector2Int(0, 0), Vector2Int(w-1, 0), Vector2Int(w-1, h-1), Vector2Int(0, h-1), texture);
    mesh->faces[4] = new Face(&mesh->vertices[0], &mesh->vertices[4], &mesh->vertices[7], &mesh->vertices[3],
                    Vector2Int(0, 0), Vector2Int(w-1, 0), Vector2Int(w-1, h-1), Vector2Int(0, h-1), texture);
    mesh->faces[5] = new Face(&mesh->vertices[5], &mesh->vertices[1], &mesh->vertices[2], &mesh->vertices[6],
                    Vector2Int(0, 0), Vector2Int(w-1, 0), Vector2Int(w-1, h-1), Vector2Int(0, h-1), texture);
    go->transform()->position.z = -500;

    GameObject *go2 = new GameObject(scene);
    meshrender = go2->AddComponent<MeshRenderer>();
    meshrender->mesh = mesh;
    go2->transform()->position.z = 100;
    //go2->transform()->position.x = 800;
    //go2->transform()->position.y -= 200;
    scene->AddGameObject(go);
    scene->AddGameObject(go2);

    /*GameObject *go3 = new GameObject(scene);
    MeshRenderer *meshrender2 = go3->AddComponent<MeshRenderer>();
    meshrender2->mesh = mesh;
    go3->transform()->position.z = 100;
    go3->transform()->position.x = 200;
    go3->transform()->position.y = 200;
    scene->AddGameObject(go3);*/
    return scene;
}

int main()
{
    ParticuleEssentialInit();
    ParticuleEngineInit();
    window = new Window();//800, 600, "Demo");
    sceneManager->AddScene(LoadScene1);
    sceneManager->LoadScene(0);
    
    printf("MeshRenderer: %p\n", meshrender);
    printf("Camera: %p\n", Camera::mainCamera);
    while (window->IsRunning())
    {
        window->Clear();
        Camera::mainCamera->bufferRenderer->Clear();
        meshrender->CalculateProjection(Camera::mainCamera);
        meshrender->mesh->DrawInBuffer(Camera::mainCamera);
        Camera::mainCamera->bufferRenderer->Draw();
        meshrender->gameObject->transform()->rotation.y += 0.001;
        meshrender->gameObject->transform()->rotation.z += 0.001;
        input->Update();
        window->Update();
    }
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    return 0;
}