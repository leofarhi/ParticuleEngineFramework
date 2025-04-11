#ifndef SDL2_HPP
#define SDL2_HPP
#include <string>

namespace sdl2
{
    // Include the SDL header files
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    //#include <SDL/SDL_mixer.h>

    inline std::string SDL2_GetError()
    {
        return std::string(SDL_GetError());
    }
}

#endif // SDL2_HPP