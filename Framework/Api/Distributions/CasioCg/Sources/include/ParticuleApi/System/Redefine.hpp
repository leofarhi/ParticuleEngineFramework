#ifndef REDEFINE_HPP
#define REDEFINE_HPP
#include <ParticuleApi/System/Input.hpp>
#include <ParticuleApi/System/Resource.hpp>

namespace Particule::Api
{
    #ifndef PlayerInput
    #define PlayerInput(str) Input()
    #endif

    #ifndef GetResource
    #define GetResource(str) Resource(str)
    #endif
}

#endif // REDEFINE_HPP