#ifndef PARTICLE
#define PARTICLE

#include <SFML/Graphics.h>

typedef enum _ParticleType { EMPTY = 0, SOLID = 1, SAND = 2, WATER = 3 } ParticleType;

typedef struct _ActiveParticle
{
    ParticleType type;
    float x, y;
    float vx, vy;
} ActiveParticle;

typedef struct _Particle
{
    ParticleType type;
} Particle;

sfColor getColor(ParticleType type);

#endif