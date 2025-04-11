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

    /*Exemple de redéfinition de PlayerInput pour le compilateur GCC
    #define PlayerInput(str)(\
        (__builtin_constant_p(str) && __builtin_strcmp(str, "A") == 0) ? Input(gint::KEY_UP) : \
        (__builtin_constant_p(str) && __builtin_strcmp(str, "B") == 0) ? Input(gint::KEY_DOWN) : \
        Input()\
        )
    */
}

#endif // REDEFINE_HPP