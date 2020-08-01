#ifndef PARTICLE_SIMULATOR
#define PARTICLE_SIMULATOR

#include "Particle.h"
#include "ParticleRenderer.h"

void ps_init(int w_width, int w_height);
void ps_terminate();
void ps_update(float dt);

Particle* getParticles();
Particle* getParticle(int x, int y);
void setParticleType(int x, int y, ParticleType type);

#endif