#include "ParticleSimulator.h"
#include "list.h"

#include <stdbool.h>

#define GRAVITY 0.001
#define WATER_SFV 30 //Spread factor velocity

Particle* particles;
List activeParticles;
int ps_width, ps_height;

Particle* getParticle(int x, int y) { return &particles[y*ps_width + x]; }

ParticleType* getParticleType(int x, int y) { return &getParticle(x,y)->type; }

void updateParticleTypeAt(int x, int y, ParticleType type)
{
    getParticle(x, y)->type = type;
    updatePixel(x, y, type);
}

void updateParticleAt(int x, int y, Particle particle)
{
    *getParticle(x, y) = particle;
    updatePixel(x, y, particle.type);
}

void addParticle(int x, int y, Particle particle)
{
    updateParticleAt(x, y, particle);
    
    if(particle.type != SOLID && particle.type != EMPTY)
    {
        ActiveParticle* p = malloc(sizeof(ActiveParticle));
        p->type = particle.type;
        p->x = x;
        p->y = y;
        p->vx = 0;
        p->vy = 0;
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
            ActiveParticle* p = ap->element;
            if(p->x == x && p->y == y)
            {
                free( rem(&activeParticles, ap) );
                break;
            }
        }
    }

    updateParticleTypeAt(x, y, EMPTY);
}

void ps_init(int w_width, int w_height)
{
    ps_width = w_width;
    ps_height = w_height;
    particles = malloc(sizeof(Particle) * ps_width * ps_height);

    for(int y = 0; y < ps_height; y++)
    {
        for(int x = 0; x < ps_width; x++)
        {
            if(y == 0 || y == ps_height-1 || x == 0 || x == ps_width-1) updateParticleTypeAt(x, y, SOLID);
            else updateParticleTypeAt(x, y, EMPTY);
        }
    }

    initList(&activeParticles, sizeof(ActiveParticle));
}

void ps_terminate()
{
    free(particles);
    clearList(&activeParticles);
}

static void updateSand(ActiveParticle* p, float dt)
{
    float init_x = p->x;
    float init_y = p->y;
    p->vy += GRAVITY*dt;

    bool collision = false;

    for(int i = 0; i <= p->vy && !collision; i++)
    {
        float dy = ( i != (int)p->vy ? 1 : p->vy - i );
        p->y += dy;

        if((int)p->y != (int)init_y)
        {
            if(*getParticleType(p->x, p->y) == SOLID)
                collision = true;
            else if(*getParticleType(p->x, p->y) == SAND)
            {
                if(*getParticleType(p->x+1, p->y) == EMPTY || *getParticleType(p->x+1, p->y) == WATER)
                    p->x += 1;
                else if(*getParticleType(p->x-1, p->y) == EMPTY || *getParticleType(p->x-1, p->y) == WATER)
                    p->x -= 1;
                else
                    collision = true;
            }

            if(collision)
            {
                p->y = init_y;
                p->vy = 0;
            }

            if(*getParticleType(p->x, p->y) == WATER)
            {
                removeParticle(p->x, p->y);
            }
        }

        updateParticleTypeAt(init_x, init_y, EMPTY);
        updateParticleTypeAt(p->x, p->y, SAND);

        init_x = p->x;
        init_y = p->y;
    }
}

static void updateWater(ActiveParticle* p, float dt)
{
    float init_x = p->x;
    float init_y = p->y;
    p->vy += GRAVITY*dt;

    bool collision = false;

    for(int i = 0; i <= p->vy && !collision; i++)
    {
        float dy = ( i != (int)p->vy ? 1 : p->vy - i );
        p->y += dy;

        if((int)p->y != (int)init_y)
        {
            if(*getParticleType(p->x, p->y) == SOLID || *getParticleType(p->x, p->y) == SAND)
                collision = true;
            else if(*getParticleType(p->x, p->y) == WATER)
            {
                if(*getParticleType(p->x+1, p->y) == EMPTY)
                    p->x += 1;
                else if(*getParticleType(p->x-1, p->y) == EMPTY)
                    p->x -= 1;
                else
                    collision = true;
            }

            if(collision)
            {
                p->y = init_y;
                p->vy = 0;
            }

            updateParticleTypeAt(init_x, init_y, EMPTY);
            updateParticleTypeAt(p->x, p->y, WATER);
        }

        init_x = p->x;
        init_y = p->y;
    }

    // if(collision)
    // {
    //     p->y = init_y;
    //     p->vy = 0;

    //     int direction = rand() % 2;
    //     if(direction == 0) direction = -1;

    //     if(*getParticleType(p->x+direction, p->y) == EMPTY)
    //         p->x += direction;
    //     else if(*getParticleType(p->x-direction, p->y) == EMPTY)
    //         p->x -= direction;
    // }

    if(collision)
    {
        collision = false;
        p->vx = WATER_SFV*dt;

        int direction = rand() % 2;
        if(direction == 0) direction = -1;

        for(int i = 0; i <= p->vx && !collision; i++)
        {
            float dx = ( i != (int)p->vx ? 1 : p->vx - i ) * direction;
            p->x += dx;

            if((int)p->x != (int)init_x)
            {
                if(*getParticleType(p->x, p->y) != EMPTY)
                {
                    collision = true;
                    p->x = init_x;
                }

                updateParticleTypeAt(init_x, init_y, EMPTY);
                updateParticleTypeAt(p->x, p->y, WATER);
            }

            init_x = p->x;
        }
    }
}

static void updateParticle(ActiveParticle* p, float dt)
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
        updateParticle((ActiveParticle*)ap->element, dt);
    }
}