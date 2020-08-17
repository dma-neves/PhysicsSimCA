#ifndef PARTICLE
#define PARTICLE

#include <SFML/Graphics.h>

typedef enum _ParticleType { EMPTY = 0, SOLID, SAND, WATER } ParticleType;

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