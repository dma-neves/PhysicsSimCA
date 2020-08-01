#ifndef PARTICLE
#define PARTICLE

#include <SFML/Graphics.h>

typedef enum _ParticleType { EMPTY = 0, SOLID, SAND, WATER } ParticleType;

typedef struct _Particle
{
    ParticleType type;
    float x, y;
} Particle;

sfColor getColor(ParticleType type);

#endif