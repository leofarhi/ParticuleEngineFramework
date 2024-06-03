#ifndef PE_ENUM_LAYER_HPP
#define PE_ENUM_LAYER_HPP

namespace Particule::Enum
{
    typedef int Layer;

    #define layerDefault 0
    #define layerTransparentFX 1
    #define layerIgnoreRaycast 2
    #define layerWater 4
    #define layerUI 5
    #define layerPostProcessing 8
}

#endif // PE_ENUM_LAYER_HPP