#include "ParticleRenderer.h"

#include <stdbool.h>
#include <stdlib.h>

sfUint8* pixels;
int pr_width, pr_height;

sfSprite* sprite;
sfIntRect area;

void pr_init(int w_width, int w_height, float scale)
{
    pr_width = w_width;
    pr_height = w_height;

    pixels = malloc(pr_width*pr_height*4);

    area.left = 0;
    area.top = 0;
    area.width = pr_width;
    area.height = pr_height;
    sprite = sfSprite_create();

    sfVector2f scale_v;
    scale_v.x = scale;
    scale_v.y = scale;
    sfSprite_setScale(sprite, scale_v);
}

void pr_destroy()
{
    free(pixels);
}


static void setPixel(int x, int y, int r, int g, int b, int a)
{
    pixels[ (x + y * pr_width) * 4] = r;
    pixels[ (x + y * pr_width) * 4 + 1] = g;
    pixels[ (x + y * pr_width) * 4 + 2] = b;
    pixels[ (x + y * pr_width) * 4 + 3] = a;
}

void updatePixel(int x, int y, ParticleType type)
{
    sfColor color = getColor(type);
    setPixel(x, y, color.r, color.g, color.b, color.a);
}

void pr_render(sfRenderWindow* window)
{
    sfImage* image = sfImage_createFromPixels(pr_width, pr_height, pixels);
    sfTexture* texture = sfTexture_createFromImage(image, &area);
    sfSprite_setTexture(sprite, texture, false);

    sfRenderWindow_drawSprite(window, sprite, NULL);

    sfImage_destroy(image);
    sfTexture_destroy(texture);
}