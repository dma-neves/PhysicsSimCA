#include "PhysicsSim.h"
#include "ParticleSimulator.h"
#include "ParticleRenderer.h"

#include <SFML/Graphics.h>
#include <stdbool.h>
#include <stdio.h>

#define UPDATE_PERIOD 0.08

sfRenderWindow* window;
sfVideoMode mode;
sfEvent event;
sfClock* clock;
bool running = true;

void init(int width, int height, char* title)
{
    mode.height = height;
    mode.width = width;
    mode.bitsPerPixel = 32;

    window = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    clock = sfClock_create();

    pr_init(width, height);
    ps_init(width, height);
}

static void handleEvents()
{
    while(sfRenderWindow_pollEvent(window, &event))
    {
        if(event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
        {
            running = false;
            sfRenderWindow_close(window);
        }
    }
}

static void update(float dt)
{
    ps_update(dt);
}

static void render()
{
    sfRenderWindow_clear(window, sfBlack);

    pr_render(window);

    sfRenderWindow_display(window);
}

static void terminate()
{
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);

    ps_terminate();
    pr_terminate();
}

void run()
{
    while(running)
    {
        handleEvents();

        float dt = sfTime_asSeconds( sfClock_getElapsedTime(clock) );
        if(dt >= UPDATE_PERIOD)
        {
            sfClock_restart(clock);
            
            update(dt);
            render();
        }
    }

    terminate();
}