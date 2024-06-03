#ifndef PE_SCENE_HPP
#define PE_SCENE_HPP

#include <ParticuleEssential/Types/List.hpp>
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>

namespace Particule::SceneManagement
{
    using namespace Particule::Core;

    class Scene
    {
    public:
        String name;
        List<GameObject*> gameObjects;

        Scene(String name);
        ~Scene();
        void AddGameObject(GameObject *gameObject);
        void RemoveGameObject(GameObject *gameObject);
        GameObject* FindGameObject(String name);
    };
}

#endif // PE_SCENE_HPP