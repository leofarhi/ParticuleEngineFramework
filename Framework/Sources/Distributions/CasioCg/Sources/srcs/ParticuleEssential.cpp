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
        Window::DrawingWindow = nullptr;
        Window::MainWindow = nullptr;
        InitBasic();
        new VirtualResources();
    }

    void ParticuleEssentialQuit()
    {
        if (Window::MainWindow != nullptr)
            delete Window::MainWindow;
        delete VirtualResources::Instance;
    }
}