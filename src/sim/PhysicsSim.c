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

#define NUM_BUTTONS 4
Button* buttons[NUM_BUTTONS];
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

    for(int i = 0; i < NUM_BUTTONS; i++)
        buttons[i] = button_create(10, 10+30*i, 20, 20, getColor(i));
}

void destroy()
{
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);

    ps_destroy();
    pr_destroy();

    for(int i = 0; i < NUM_BUTTONS; i++)
        button_destroy(buttons[i]);
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

        bool toolSelected = false;
        for(int i = 0; i < NUM_BUTTONS && !toolSelected; i++)
        {
            if(button_over(buttons[i], pos.x, pos.y))
            {
                tool = i;
                toolSelected = true;
            }
        }

        if(!toolSelected)
        {
            if(tool == EMPTY)
                removeParticle(pos.x/scale, pos.y/scale);
            else if(*getParticleType(pos.x/scale, pos.y/scale) == EMPTY) addParticle(pos.x/scale, pos.y/scale, (Particle){.type = tool});
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

    for(int i = 0; i < NUM_BUTTONS; i++)
        button_render(buttons[i], window);

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