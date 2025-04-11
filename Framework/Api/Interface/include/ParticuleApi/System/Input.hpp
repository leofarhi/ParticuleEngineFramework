#ifndef INPUT_HPP
#define INPUT_HPP
#include <ParticuleApi/Types/Vector2.hpp>
#include <ParticuleApi/Types/Fixed.hpp>

namespace Particule::Api
{
    class Input
    {
    public:
        Input();
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