#ifndef INPUT_HPP
#define INPUT_HPP
#include <ParticuleApi/Types/Vector2.hpp>
#include <ParticuleApi/Types/Fixed.hpp>

#include <ParticuleApi/System/gint.hpp>

namespace Particule::Api
{
    class Input
    {
    private:
        int m_key;
    public:
        Input();
        Input(int key);
        Input(const Input& other);
        Input& operator=(const Input& other);
        ~Input();
        bool IsKeyPressed();
        bool IsKeyDown();
        bool IsKeyUp();
        fixed_t Get1DAxis();
        Vector2<fixed_t> Get2DAxis();
    };
}

#endif // INPUT_HPP