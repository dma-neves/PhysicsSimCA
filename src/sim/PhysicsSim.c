#include "PhysicsSim.h"

#include <SFML/Graphics.h>
#include <stdbool.h>
#include <stdio.h>

#define UPDATE_PERIOD 0.08

sfRenderWindow* window;
sfVideoMode mode;
sfEvent event;
sfClock* clock;
bool running = true;

#define WIDTH 600
#define HEIGHT 600

sfImage* image;
sfSprite* sprite;
sfUint8 pixels[WIDTH*HEIGHT*4];

void init(int width, int height, char* title)
{
    mode.height = height;
    mode.width = width;
    mode.bitsPerPixel = 32;

    window = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    clock = sfClock_create();
    
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            pixels[ (x + y * WIDTH) * 4]     = 255; // R?
            pixels[ (x + y * WIDTH) * 4 + 1] = 0; // G?
            pixels[ (x + y * WIDTH) * 4 + 2] = 0; // B?
            pixels[ (x + y * WIDTH) * 4 + 3] = 255; // A?

            
        }
    }

    image = sfImage_createFromPixels(WIDTH, HEIGHT, pixels);

    sfIntRect area;
    area.left = 0;
    area.top = 0;
    area.width = WIDTH;
    area.height = HEIGHT;
    sfTexture* texture = sfTexture_createFromImage(image, &area);
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, false);
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

static void update()
{
}

static void render()
{
    sfRenderWindow_clear(window, sfBlack);

    sfRenderWindow_drawSprite(window, sprite, NULL);

    sfRenderWindow_display(window);
}

static void terminate()
{
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);
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
            
            update();
            render();
        }
    }

    terminate();
}