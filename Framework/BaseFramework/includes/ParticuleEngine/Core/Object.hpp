#ifndef PE_CORE_OBJECT_HPP
#define PE_CORE_OBJECT_HPP
#include <ParticuleEssential/Types/String.hpp>

namespace Particule::Core
{
    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;
        virtual const String __class__() { return "Object";}
    };
}

#endif // PE_CORE_OBJECT_HPP