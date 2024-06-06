#include <ParticuleEssential/ParticuleEssential.hpp>
#include "./../includes/ParticuleEssential/Graphic/Window.hpp"
#include "./../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace Particule::Essential::Graphic;
using namespace Particule::Essential::Input;


namespace Particule::Essential
{
    void ParticuleEssentialInit()
    {
        input = new InputManager();
    }

    void ParticuleEssentialQuit()
    {
        if (window != nullptr)
            delete window;
        
        delete input;
        //PC_QuitAsset();
    }
}