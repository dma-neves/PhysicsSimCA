#ifndef PARTICLE
#define PARTICLE

typedef enum _ParticleType { EMPTY = 0, SOLID, SAND, WATER } ParticleType;

typedef struct _Particle
{
    ParticleType type;
} Particle;

#endif