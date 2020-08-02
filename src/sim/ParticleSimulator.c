#include "ParticleSimulator.h"
#include "list.h"

ParticleType* particles;
List activeParticles;
int ps_width, ps_height;

void setParticleType(int x, int y, ParticleType type)
{
    *getParticleType(x,y) = type;
    updatePixel(x, y, type);
}

void ps_init(int w_width, int w_height)
{
    ps_width = w_width;
    ps_height = w_height;
    particles = malloc(sizeof(ParticleType) * ps_width * ps_height);

    for(int y = 0; y < ps_height; y++)
    {
        for(int x = 0; x < ps_width; x++)
        {
            if(y == 0 || y == ps_height-1 || x == 0 || x == ps_width-1) setParticleType(x, y, SOLID);
            else setParticleType(x, y, EMPTY);
        }
    }

    initList(&activeParticles, sizeof(Particle));
}

void ps_terminate()
{
    free(particles);
    clearList(&activeParticles);
}

static void updateSand(Particle* p, float dt)
{
    float init_x = p->x;
    float init_y = p->y;
    p->y += dt;

    if((int)p->y != (int)init_y)
    {
        if(*getParticleType(p->x, p->y) == SOLID)
            p->y = init_y;
        else if(*getParticleType(p->x, p->y) == SAND)
        {
            if(*getParticleType(p->x+1, p->y) == EMPTY)
                p->x++;
            else if(*getParticleType(p->x-1, p->y) == EMPTY)
                p->x--;
            else
                p->y = init_y;
        }

        setParticleType(init_x, init_y, EMPTY);
        setParticleType(p->x, p->y, p->type);
    }
}

static void updateWater(Particle* p, float dt)
{
}

static void updateParticle(Particle* p, float dt)
{
    switch(p->type)
    {
        case SAND: updateSand(p, dt); break;
        case WATER: updateWater(p, dt); break;
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

ParticleType* getParticleType(int x, int y)
{
    return &particles[y*ps_width + x];
}

void addParticle(int x, int y, ParticleType type)
{
    setParticleType(x, y, type);
    
    if(type != SOLID && type != EMPTY)
    {
        Particle* p = malloc(sizeof(Particle));
        p->type = type;
        p->x = x;
        p->y = y;
        add(&activeParticles, p);
    }
}

void removeParticle(int x, int y)
{
    if(*getParticleType(x, y) != EMPTY && *getParticleType(x, y != SOLID))
    {
        Node* ap = activeParticles.head;
        for(; ap != NULL; ap = ap->next)
        {
            Particle* p = ap->element;
            if(p->x == x && p->y == y)
            {
                free( rem(&activeParticles, ap) );
                break;
            }
        }
    }

    setParticleType(x, y, EMPTY);
}