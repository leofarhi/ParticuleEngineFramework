#ifndef COMMON_SCE_HPP
#define COMMON_SCE_HPP

#include <stdio.h>

namespace Particule::Essential::Distribution
{
    
    #include <pspkernel.h>
    #include <pspgu.h>
    #include <pspgum.h>
    #include <pspge.h>
    #include <pspdisplay.h>

    #define PSP_BUF_WIDTH (512)
    #define PSP_SCR_WIDTH (480)
    #define PSP_SCR_HEIGHT (272)

    unsigned int __attribute__((aligned(16))) PSP_list[262144];

    unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm);

    // Vram Buffer Request
    void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm);

    // Vram Texture Request
    void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm);

    int exit_callback(int arg1, int arg2, void* common);

    int callback_thread(SceSize args, void* argp);

    int SetupCallbacks(void);

    void initGraphics(void);

    void termGraphics();
    
}

#endif // COMMON_SCE_HPP