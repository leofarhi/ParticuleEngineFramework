#ifndef COMPONENTS_FREECAM_HPP
#define COMPONENTS_FREECAM_HPP

#include <ParticuleEngine/Core/Component.hpp>
using namespace Particule::Core;

class FreeCam : public Component
{
public:
    FreeCam(GameObject *gameObject);
    ~FreeCam() override;
    virtual const String __class__() { return "FreeCam";}

    void Update() override;
};


#endif // COMPONENTS_FREECAM_HPP