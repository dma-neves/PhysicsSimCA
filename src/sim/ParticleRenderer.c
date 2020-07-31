#include "ParticleRenderer.h"

#include <stdbool.h>
#include <stdlib.h>

sfUint8* pixels;
int width, height;

sfImage* image;
sfSprite* sprite;
sfTexture* texture;

void pr_init(int w_width, int w_height)
{
    width = w_width;
    height = w_height;

    pixels = malloc(width*height*4);

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            pixels[ (x + y * width) * 4]     = 255; // R?
            pixels[ (x + y * width) * 4 + 1] = 0; // G?
            pixels[ (x + y * width) * 4 + 2] = 0; // B?
            pixels[ (x + y * width) * 4 + 3] = 255; // A?
        }
    }

    image = sfImage_createFromPixels(width, height, pixels);

    sfIntRect area;
    area.left = 0;
    area.top = 0;
    area.width = width;
    area.height = height;
    sfTexture* texture = sfTexture_createFromImage(image, &area);
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, false);
}

void pr_terminate()
{
    free(pixels);
}

void pr_render(sfRenderWindow* window)
{
    sfRenderWindow_drawSprite(window, sprite, NULL);
}