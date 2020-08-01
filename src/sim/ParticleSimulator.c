#include "ParticleSimulator.h"
#include "list.h"

Particle* particles;
List activeParticles;
int ps_width, ps_height;

void setParticleType(int x, int y, ParticleType type)
{
    getParticle(x,y)->type = type;
    updatePixel(x, y, type);
}

void ps_init(int w_width, int w_height)
{
    ps_width = w_width;
    ps_height = w_height;
    particles = malloc(sizeof(Particle) * ps_width * ps_height);

    for(int y = 0; y < ps_height; y++)
    {
        for(int x = 0; x < ps_width; x++)
            setParticleType(x,y,EMPTY);
    }

    initList(&activeParticles, sizeof(Particle));
}

void ps_terminate()
{
    free(particles);
}

static void updateSand(Particle* p, float dt)
{
}

static void updateWater(Particle* p, float dt)
{
}

static void updateParticle(Particle* p, float dt)
{
    switch(p->type)
    {
        case SAND: updateSand(p, dt);
        case WATER: updateWater(p, dt);
    }
}

void ps_update(float dt)
{
    Node* ap = activeParticles.head;
    for(; ap != NULL; ap = ap->next)
    {
        updateParticle((Particle*)ap->element, dt);
    }
}

Particle* getParticles()
{
    return particles;
}

#include <stdio.h>

Particle* getParticle(int x, int y)
{
    return &particles[y*ps_width + x];
}