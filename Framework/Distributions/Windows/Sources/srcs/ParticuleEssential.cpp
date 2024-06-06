#include <ParticuleEssential/ParticuleEssential.hpp>
#include "./../includes/ParticuleEssential/Graphic/Window.hpp"
#include "./../includes/ParticuleEssential/Input/Input.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

using namespace Particule::Essential::Graphic;
using namespace Particule::Essential::Input;

static void ResetDirectory()
{
    // Obtenez le chemin absolu du programme
    char *path = SDL_GetBasePath();
    if (path == NULL)
        error_exit(EXIT_FAILURE, "error SDL_GetBasePath %s", SDL_GetError());

    // Changez le répertoire de travail
    if (chdir(path) != 0)
        error_exit(EXIT_FAILURE, "error chdir %s", SDL_GetError());

    // Libérez la mémoire
    //printf("path: %s\n", path);
    SDL_free(path);
}

namespace Particule::Essential
{
    void ParticuleEssentialInit()
    {
        // Initializes the SDL.
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            error_exit(EXIT_FAILURE, "error Init %s", SDL_GetError());
        ResetDirectory();
        // Initializes the image library.
        if (IMG_Init(IMG_INIT_PNG) == 0)
            error_exit(EXIT_FAILURE, "error IMG_Init %s", IMG_GetError());

        // Initializes the font library.
        if (TTF_Init() == -1)
            error_exit(EXIT_FAILURE, "error TTF_Init %s", TTF_GetError());

        input = new InputManager();
    }

    void ParticuleEssentialQuit()
    {
        if (window != nullptr)
            delete window;
        // Quits the font library.
        TTF_Quit();
        // Quits the image library.
        IMG_Quit();
        SDL_Quit();
        delete input;
        //PC_QuitAsset();
    }
}