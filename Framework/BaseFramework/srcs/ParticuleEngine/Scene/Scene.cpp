#include <ParticuleEngine/Scene/Scene.hpp>

namespace Particule::SceneManagement
{
    Scene::Scene(String name)
    {
        this->name = name;
    }

    Scene::~Scene()
    {
        for (ListNode<GameObject *> *cur=nullptr; this->gameObjects.ForEach(&cur);)
        {
            delete cur->data;
        }
    }

    void Scene::AddGameObject(GameObject *gameObject)
    {
        gameObjects.Append(gameObject);
    }

    void Scene::RemoveGameObject(GameObject *gameObject)
    {
        gameObjects.Remove(gameObject);
    }

    GameObject* Scene::FindGameObject(String name)
    {
        for (ListNode<GameObject *> *cur=nullptr; this->gameObjects.ForEach(&cur);)
        {
            if (cur->data->name == name)
            {
                return cur->data;
            }
        }
        return nullptr;
    }
}