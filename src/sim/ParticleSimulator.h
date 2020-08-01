#ifndef PARTICLE_SIMULATOR
#define PARTICLE_SIMULATOR

typedef enum _ParticleType { EMPTY = 0, SOLID, SAND, WATER } ParticleType;

typedef struct _Particle
{
    ParticleType type;
} Particle;

void ps_init(int w_width, int w_height);
void ps_terminate();
void ps_update(float dt);

Particle* getParticles();
Particle* getParticle(int x, int y);

#endif