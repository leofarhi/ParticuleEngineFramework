#include <ParticuleEssential/ParticuleEssential.hpp>
#include <ParticuleEssential/System/VirtualFile.hpp>
#include <ParticuleEssential/Basic/Basic.hpp>
#include "./../includes/ParticuleEssential/Graphic/Window.hpp"
#include "./../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../includes/ParticuleEssential/System/Distribution/Psp/common-sce.hpp"

namespace Particule::Essential
{

    using namespace Particule::Essential::Distribution;

    void ParticuleEssentialInit()
    {
        Window::DrawingWindow = nullptr;
        Window::MainWindow = nullptr;
        InitBasic();


        SetupCallbacks();
        initGraphics();

        sceCtrlSetSamplingCycle(0);
        sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);


        new VirtualResources();
    }

    void ParticuleEssentialQuit()
    {
        if (Window::MainWindow != nullptr)
            delete Window::MainWindow;
        //TODO
        delete VirtualResources::Instance;
        termGraphics();
        sceKernelExitGame();
    }
}