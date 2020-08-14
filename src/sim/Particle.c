#include "Particle.h"

sfColor getColor(ParticleType type)
{
    sfColor color;
    color.a = 255;
    switch(type)
    {
        case EMPTY:
            color.r = 0; color.g = 0; color.b = 0;
            break;

        case SOLID:
            color.r = 100; color.g = 100; color.b = 100;
            break;

        case SAND:
            color.r = 243; color.g = 252; color.b = 127;
            break;

        case WATER:
            color.r = 68; color.g = 154; color.b = 255;
            break;
    }

    return color;
}