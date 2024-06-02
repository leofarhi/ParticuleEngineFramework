#include "../../../includes/ParticuleEssential/Input/Input.hpp"

Input::Input()
{
    mouse = new Mouse();
    InputEvents = new List<void*>();
    InputEventsHeld = new List<void*>();
}

Input::~Input()
{
    delete mouse;
    delete InputEvents;
    delete InputEventsHeld;
}