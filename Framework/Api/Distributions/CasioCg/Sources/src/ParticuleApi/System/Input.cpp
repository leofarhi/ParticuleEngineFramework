#include <ParticuleApi/System/Input.hpp>

namespace Particule::Api
{
    Input::Input() : m_key(0) {}
    Input::Input(int key) : m_key(key) {}
    Input::Input(const Input& other) : m_key(other.m_key) {}
    Input& Input::operator=(const Input& other) { m_key = other.m_key; return *this; }
    Input::~Input() {}

    bool Input::IsKeyPressed() { return gint::keypressed(m_key); }
    bool Input::IsKeyDown() { return gint::keydown(m_key); }
    bool Input::IsKeyUp() { return gint::keyreleased(m_key); }
    fixed_t Input::Get1DAxis() { return 0; }
    Vector2<fixed_t> Input::Get2DAxis() { return Vector2<fixed_t>(0, 0); }
}