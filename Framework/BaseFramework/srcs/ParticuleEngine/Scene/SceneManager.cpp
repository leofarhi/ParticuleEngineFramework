#include <ParticuleEngine/Scene/SceneManager.hpp>

namespace Particule::SceneManagement
{
    SceneManager *sceneManager = nullptr;

    SceneManager::SceneManager()
    {
        sceneManager = this;
    }

    SceneManager::~SceneManager()
    {
        for (ListNode<Scene *> *cur = nullptr; loadedScenes.ForEach(&cur);)
        {
            delete cur->data;
        }
    }

    void SceneManager::AddScene(Scene* (*loadScene)(void))
    {
        availableScenes.Append(loadScene);
    }

    void SceneManager::LoadScene(int index)
    {
        Scene *scene = availableScenes[index]();
        loadedScenes.Append(scene);
    }

    void SceneManager::UnloadScene(Scene *scene)
    {
        loadedScenes.Remove(scene);
        delete scene;
    }

    void SceneManager::UnloadScene(String name)
    {
        for (ListNode<Scene *> *cur = nullptr; loadedScenes.ForEach(&cur);)
        {
            if (cur->data->name == name)
            {
                loadedScenes.Remove(cur->data);
                delete cur->data;
                break;
            }
        }
    }

    Scene *SceneManager::GetScene(String name)
    {
        for (ListNode<Scene *> *cur = nullptr; loadedScenes.ForEach(&cur);)
        {
            if (cur->data->name == name)
            {
                return cur->data;
            }
        }
        return nullptr;
    }

    Scene *SceneManager::activeScene()
    {
        return loadedScenes.First();
    }
}