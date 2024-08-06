#include "../../../../../includes/ParticuleEssential/System/Distribution/Psp/common-sce.hpp"

#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>
#include <pspdisplay.h>
#include <stdio.h>

#include <pspkernel.h>

namespace Particule::Essential::Distribution
{
    // Get Memory Size
    unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm)
    {
        switch (psm)
        {
            case GU_PSM_T4:
                return (width * height) >> 1;

            case GU_PSM_T8:
                return width * height;

            case GU_PSM_5650:
            case GU_PSM_5551:
            case GU_PSM_4444:
            case GU_PSM_T16:
                return 2 * width * height;

            case GU_PSM_8888:
            case GU_PSM_T32:
                return 4 * width * height;

            default:
                return 0;
        }
    }

    // Vram Buffer Request
    void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm)
    {
        static unsigned int staticOffset = 0;
        unsigned int memSize = getMemorySize(width,height,psm);
        void* result = (void*)staticOffset;
        staticOffset += memSize;

        return result;
    }

    // Vram Texture Request
    void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm)
    {
        void* result = getStaticVramBuffer(width,height,psm);
        return (void*)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
    }

    int exit_callback(int arg1, int arg2, void* common)
    {
        sceKernelExitGame();
        return 0;
    }

    int callback_thread(SceSize args, void* argp)
    {
        int cbid;

        cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
        sceKernelRegisterExitCallback(cbid);

        sceKernelSleepThreadCB();

        return 0;
    }

    int SetupCallbacks(void)
    {
        int thid = 0;

        thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
        if (thid >= 0)
        {
            sceKernelStartThread(thid, 0, 0);
        }

        return thid;
    }

    void initGraphics(void) {
        void* list = PSP_list;
        void* fbp0 = getStaticVramBuffer(PSP_BUF_WIDTH,PSP_SCR_HEIGHT,GU_PSM_8888);
        void* fbp1 = getStaticVramBuffer(PSP_BUF_WIDTH,PSP_SCR_HEIGHT,GU_PSM_8888);
        void* zbp = getStaticVramBuffer(PSP_BUF_WIDTH,PSP_SCR_HEIGHT,GU_PSM_4444);

        sceGuInit();

        sceGuStart(GU_DIRECT,list);
        sceGuDrawBuffer(GU_PSM_8888,fbp0,PSP_BUF_WIDTH);
        sceGuDispBuffer(PSP_SCR_WIDTH,PSP_SCR_HEIGHT,fbp1,PSP_BUF_WIDTH);
        sceGuDepthBuffer(zbp,PSP_BUF_WIDTH);

        sceDisplayWaitVblankStart();
        sceGuDisplay(GU_TRUE);
    }

    void termGraphics() {
        sceGuTerm();
    }
}