#include "ParticleSimulator.h"
#include "list.h"

Particle* particles;
List activeParticles;
int width_test, height_test;

void ps_init(int w_width, int w_height)
{
    width_test = w_width;
    height_test = w_height;
    particles = malloc(sizeof(Particle) * width_test * height_test);

    for(int y = 0; y < height_test; y++)
    {
        for(int x = 0; x < width_test; x++)
            getParticle(x, y)->type = EMPTY;
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

Particle* getParticle(int x, int y)
{
    return &particles[y*width_test + x];
}