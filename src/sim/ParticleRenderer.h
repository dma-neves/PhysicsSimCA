#ifndef PARITCLE_RENDERER
#define PARTICLE_RENDERER

#include <SFML/Graphics.h>

#include "ParticleSimulator.h"

void pr_init(int w_width, int w_height);
void pr_terminate();
void pr_render(sfRenderWindow* window);

#endif