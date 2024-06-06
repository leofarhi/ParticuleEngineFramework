#ifndef PE_BASIC_HPP
#define PE_BASIC_HPP
#include <math.h>

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#define truemod(a,b) ((a % b + b) % b)

#define clamp(a, b, c) (min(max(a, b), c))
#define lerp(a, b, t) (a + (b - a) * t)
#define invlerp(a, b, t) ((t - a) / (b - a))

#define int_to_ptr(a) ((void*)(size_t)(a))
#define ptr_to_int(a) ((int)(size_t)(a))

#define PI 3.14159265358979323846

#define DEG_TO_RAD(a) (a * PI / 180.0)

#define RAD_TO_DEG(a) (a * 180.0 / PI)

#define EPSILON 0.00001

void init_trig_tables();

float sin_approx(float i);

float cos_approx(float i);

void InitBasic();




#endif // PE_BASIC_HPP