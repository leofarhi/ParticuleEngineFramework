#ifndef PE_ENUM_TAG_HPP
#define PE_ENUM_TAG_HPP

namespace Particule::Enum
{
    typedef int Tag;

    #define tagUntagged 0
    #define tagPlayer 1
    #define tagEnemy 2
    #define tagWall 3
    #define tagGround 4
    #define tagBullet 5
    #define tagMainCamera 6
    #define tagPostProcessing 7
}

#endif // PE_ENUM_TAG_HPP