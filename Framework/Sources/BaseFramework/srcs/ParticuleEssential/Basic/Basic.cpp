#include <ParticuleEssential/Basic/Basic.hpp>
#include <math.h>

#define NUM_SAMPLES 360
float sin_table[NUM_SAMPLES];
float cos_table[NUM_SAMPLES];


void init_trig_tables()
{
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        sin_table[i] = sin(i * 2 * PI / NUM_SAMPLES);
        cos_table[i] = cos(i * 2 * PI / NUM_SAMPLES);
    }
}

float sin_approx(float i)
{
    return sin_table[(int)(i * NUM_SAMPLES / (2 * PI)) % NUM_SAMPLES];
}

float cos_approx(float i)
{
    return cos_table[(int)(i * NUM_SAMPLES / (2 * PI)) % NUM_SAMPLES];
}

void InitBasic()
{
    init_trig_tables();
}
