#include <ParticuleEngine/ParticuleEngine.hpp>
#include <ParticuleEngine/Scene/SceneManager.hpp>

namespace Particule::Engine
{
    using namespace Particule::SceneManagement;

    void ParticuleEngineInit()
    {
        // Initialize the engine
        SceneManager::sceneManager = new SceneManager();
    }

    void ParticuleEngineQuit()
    {
        // Quit the engine
        delete SceneManager::sceneManager;
    }
}