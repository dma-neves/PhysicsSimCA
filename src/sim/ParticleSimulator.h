#ifndef PARTICLE_SIMULATOR
#define PARTICLE_SIMULATOR

#include "Particle.h"
#include "ParticleRenderer.h"

void ps_init(int w_width, int w_height);
void ps_destroy();
void ps_update(float dt);

ParticleType* getParticleType(int x, int y);
Particle* getParticle(int x, int y);

void addParticle(int x, int y, Particle particle);
void removeParticle(int x, int y);

#endif