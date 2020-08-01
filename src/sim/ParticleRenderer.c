#include "ParticleRenderer.h"

#include <stdbool.h>
#include <stdlib.h>

sfUint8* pixels;
int width, height;

sfSprite* sprite;
sfIntRect area;

void pr_init(int w_width, int w_height)
{
    width = w_width;
    height = w_height;

    pixels = malloc(width*height*4);

    area.left = 0;
    area.top = 0;
    area.width = width;
    area.height = height;
    sprite = sfSprite_create();
}

void pr_terminate()
{
    free(pixels);
}


static void setPixel(int x, int y, int r, int b, int g, int a)
{
    pixels[ (x + y * width) * 4] = r;
    pixels[ (x + y * width) * 4 + 1] = g;
    pixels[ (x + y * width) * 4 + 2] = b;
    pixels[ (x + y * width) * 4 + 3] = a;
}

void updatePixel(int x, int y, ParticleType type)
{
    switch(type)
    {
        case EMPTY:
            setPixel(x, y, 0, 255, 0, 255);
            break;

        case SOLID:
            break;

        case SAND:
            break;

        case WATER:
            break;
    }
}

void pr_render(sfRenderWindow* window)
{
    sfImage* image = sfImage_createFromPixels(width, height, pixels);
    sfTexture* texture = sfTexture_createFromImage(image, &area);
    sfSprite_setTexture(sprite, texture, false);

    sfRenderWindow_drawSprite(window, sprite, NULL);

    sfImage_destroy(image);
    sfTexture_destroy(texture);
}