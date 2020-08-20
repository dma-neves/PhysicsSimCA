#ifndef PARITCLE_RENDERER
#define PARTICLE_RENDERER

#include <SFML/Graphics.h>

#include "Particle.h"

void pr_init(int w_width, int w_height, float scale);
void pr_destroy();
void pr_render(sfRenderWindow* window);

void updatePixel(int x, int y, ParticleType type);

#endif