#include <ParticuleEngine/Scene/SceneManager.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>
#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEssential/Graphic/Window.hpp>
#include <stdio.h>

namespace Particule::SceneManagement
{
    using namespace Particule::Essential;
    SceneManager *SceneManager::sceneManager = nullptr;

    SceneManager::SceneManager()
    {
        SceneManager::sceneManager = this;
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
        if (index < 0 || index >= availableScenes.Size())
        {
            printf("Scene index out of range (%d)\n", index);
            return;
        }
        Scene *scene = availableScenes[index]();
        loadedScenes.Append(scene);
        scene->CallAllComponents(&Component::Awake, true);
        scene->CallAllComponents(&Component::OnEnable, false);
        scene->CallAllComponents(&Component::Start, false);
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
                cur->data->CallAllComponents(&Component::OnDisable, false);
                cur->data->CallAllComponents(&Component::OnDestroy, true);
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

    void SceneManager::CallAllComponents(void (Component::*method)(), bool includeInactive)
    {
        for (ListNode<Scene *> *cur = nullptr; loadedScenes.ForEach(&cur);)
        {
            cur->data->CallAllComponents(method, includeInactive);
        }
    }

    void SceneManager::MainLoop()
    {
        CallAllComponents(&Component::FixedUpdate, false);
        CallAllComponents(&Component::Update, false);
        CallAllComponents(&Component::LateUpdate, false);
        CallAllComponents(&Component::OnRenderObject, false);
        CallAllComponents(&Component::OnRenderImage, false);
    }
}