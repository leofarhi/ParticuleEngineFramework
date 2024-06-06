#ifndef PE_SCENE_MANAGER_HPP
#define PE_SCENE_MANAGER_HPP

#include <ParticuleEssential/Types/List.hpp>
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEngine/Scene/Scene.hpp>

namespace Particule::SceneManagement
{

    class SceneManager
    {
    private:
        List<Scene* (*)(void)> availableScenes;
        List<Scene*> loadedScenes;
    public:
        SceneManager();
        ~SceneManager();
        void AddScene(Scene* (*loadScene)(void));
        void LoadScene(int index);
        void UnloadScene(Scene *scene);
        void UnloadScene(String name);

        Scene *GetScene(String name);
        Scene *activeScene();
    };

    extern SceneManager *sceneManager;
}

#endif // PE_SCENE_MANAGER_HPP