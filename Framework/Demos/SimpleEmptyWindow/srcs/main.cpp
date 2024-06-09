#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEngine/ParticuleEngine.hpp>

using namespace Particule::Core;
using namespace Particule::Engine;
using namespace Particule::SceneManagement;

int main()
{
    ParticuleEssentialInit();
    ParticuleEngineInit();
    window = new Window(800, 600, "Demo");
    while (window->IsRunning())
    {
        window->Clear();

        input->Update();
        window->Update();
    }
    ParticuleEngineQuit();
    ParticuleEssentialQuit();
    return 0;
}