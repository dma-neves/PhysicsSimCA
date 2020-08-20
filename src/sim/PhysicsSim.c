#include "PhysicsSim.h"
#include "ParticleSimulator.h"
#include "ParticleRenderer.h"
#include "Button.h"

#include <SFML/Graphics.h>
#include <stdbool.h>

#define DT_MULTIPLIER 100

sfRenderWindow* window;
sfVideoMode mode;
sfEvent event;
sfClock* clock;
bool running = true;
float scale;

Button* solidB;
Button* sandB;
Button* waterB;
Button* emptyB;
ParticleType tool = EMPTY;

void init(int width, int height, float r_scale, char* title)
{
    scale = r_scale;
    mode.height = height*scale;
    mode.width = width*scale;
    mode.bitsPerPixel = 32;

    window = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    clock = sfClock_create();

    pr_init(width, height, scale);
    ps_init(width, height);

    solidB = button_init(10, 10, 20, 20, getColor(SOLID));
    sandB = button_init(10, 40, 20, 20, getColor(SAND));
    waterB = button_init(10, 70, 20, 20, getColor(WATER));
    emptyB = button_init(10, 100, 20, 20, getColor(EMPTY));
}

void destroy()
{
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);

    ps_destroy();
    pr_destroy();

    button_destroy(solidB);
    button_destroy(sandB);
    button_destroy(waterB);
    button_destroy(emptyB);
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

    if(sfMouse_isButtonPressed(sfMouseLeft))
    {
        sfVector2i pos = sfMouse_getPositionRenderWindow(window);

        if(button_over(solidB, pos.x, pos.y)) tool = SOLID;
        else if(button_over(sandB, pos.x, pos.y)) tool = SAND;
        else if(button_over(waterB, pos.x, pos.y)) tool = WATER;
        else if(button_over(emptyB, pos.x, pos.y)) tool = EMPTY;
        else if(tool == EMPTY) removeParticle(pos.x/scale, pos.y/scale);
        else if(*getParticleType(pos.x/scale, pos.y/scale) == EMPTY) addParticle(pos.x/scale, pos.y/scale, (Particle){.type = tool});
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
    button_render(solidB, window);
    button_render(sandB, window);
    button_render(waterB, window);
    button_render(emptyB, window);

    sfRenderWindow_display(window);
}

void run()
{
    while(running)
    {
        handleEvents();

        float dt = sfTime_asSeconds( sfClock_restart(clock) ) * DT_MULTIPLIER;

        for(int i = 0; i <= dt; i++)
        {
            float pdt = i != (int)dt ? 1 : dt - i;
            update(pdt);
        }

        render();
    }

    destroy();
}