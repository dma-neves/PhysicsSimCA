#include "Button.h"

#include <stdlib.h>

Button* button_init(int x, int y, int width, int height, sfColor color)
{
    Button* button = malloc(sizeof(Button));
    button->x = x; button->y = y;
    button->width = width; button->height = height;
    button->active = false;
    button->rect = sfRectangleShape_create();

    sfVector2f pos; pos.x = x; pos.y = y;
    sfVector2f size; size.x = width; size.y = height;

    sfRectangleShape_setPosition(button->rect, pos);
    sfRectangleShape_setSize(button->rect, size);
    sfRectangleShape_setFillColor(button->rect, color);
    sfRectangleShape_setOutlineThickness(button->rect, 2);
    color.r = 255, color.g = 255; color.b = 255; color.a = 255;
    sfRectangleShape_setOutlineColor(button->rect, color);

    return button;
}

void button_destroy(Button* button)
{
    free(button);
}

void button_render(Button* button, sfRenderWindow* window)
{
    sfRenderWindow_drawRectangleShape(window, button->rect, NULL);
}

bool button_over(Button* button, int x, int y)
{
    if(x > button->x + button->width || x  < button->x) return false;
    if(y > button->y + button->height || y < button->y) return false;

    return true;
}
