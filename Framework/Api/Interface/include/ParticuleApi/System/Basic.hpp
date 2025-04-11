#ifndef PE_BASIC_HPP
#define PE_BASIC_HPP

namespace Particule::Api
{
    constexpr double MY_PI = 3.14159265358979323846;
    constexpr double MY_PI_2 = 1.57079632679489661923;

    static inline int true_mod(int a, int b) {return (a % b + b) % b;}
}


#endif // PE_BASIC_HPP