#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEssential/System/VirtualFile.hpp>
#include <ParticuleEssential/Basic/Basic.hpp>
#include "./../includes/ParticuleEssential/Graphic/Window.hpp"
#include "./../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace Particule::Essential
{
    void ParticuleEssentialInit()
    {
        InitBasic();
        input = new InputManager();
        new VirtualResources();
    }

    void ParticuleEssentialQuit()
    {
        if (window != nullptr)
            delete window;
        delete input;
        delete VirtualResources::Instance;
    }
}