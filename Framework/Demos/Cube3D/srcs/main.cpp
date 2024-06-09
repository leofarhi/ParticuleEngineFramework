#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>
#include "Freecam.hpp"

using namespace Particule::Core;
using namespace Particule::Engine;
using namespace Particule::SceneManagement;

MeshRenderer *meshrender = nullptr;

Scene *LoadScene1()
{
    Texture *texture = Texture::Load("../../assets/texture.jpg");
    printf("Texture: %p\n", texture);
    Scene *scene = new Scene("Scene1");
    GameObject *go = new GameObject(scene);
    go->AddComponent<Camera>();
    go->AddComponent<FreeCam>();
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

    return scene;
}

int main()
{
    ParticuleEssentialInit();
    ParticuleEngineInit();
    window = new Window(800, 600, "Demo");
    sceneManager->AddScene(LoadScene1);
    sceneManager->LoadScene(0);
    
    printf("MeshRenderer: %p\n", meshrender);
    printf("Camera: %p\n", Camera::mainCamera);
    while (window->IsRunning())
    {
        window->Clear();
        sceneManager->MainLoop();

        //meshrender->gameObject->transform()->rotation.y += 0.001;
        //meshrender->gameObject->transform()->rotation.z += 0.001;
        input->Update();
        window->Update();
    }
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    return 0;
}